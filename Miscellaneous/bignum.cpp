/* libraries
#include<bits/stdc++.h>
using namespace std;
typedef long long Int;
*/
constexpr int base = 1e9;
struct Num {
	vector<int> digits;
	Num() { digits.assign(1,0); }
	Num(Int x) {
		digits.clear();
		for (;x; x /= base) digits.push_back(x % base);
	}
	Num(string s) {
		while (s.size()>1 and s[0] == '0') s.erase(0,1);
		for (int i = s.size()-1; i >= 0; i -= 9) {
			int val = 0;
			for (int j = max(i-9, 0); j <= i; j++) val = 10 * val + (s[j]-'0');
			digits.push_back(val);
		}
	}
	void print() const {
		for (auto it = digits.rbegin(); it != digits.rend(); it++) {
			if (it != digits.rbegin())
// 				printf("%09d", *it),
				cout << setw(9) << setfill(0) << (*it);
			else 
// 				printf("%d", *it),
				cout << (*it);
		}
	}
};

bool operator< (const Num& a, const Num& b) {
	if (a.digits.size() != b.digits.size()) return a.digits.size() < b.digits.size();
	for (int i = (int)a.digits.size()-1; i >= 0; i--)
		if (a.digits[i] != b.digits[i]) return a.digits[i] < b.digits[i];
	return false;
}
bool operator<= (const Num& a, const Num& b) {
	if (a.digits.size() != b.digits.size()) return a.digits.size() < b.digits.size();
	for (int i = (int)a.digits.size()-1; i >= 0; i--)
		if (a.digits[i] != b.digits[i]) return a.digits[i] < b.digits[i];
	return true;
}
int get_digit(const vector<int>& x, int pos) {
	return (pos < (int) x.size()) ? x[pos] : 0;
}

Num operator+ (const Num& a, const Num& b) {
	const int n = max(a.digits.size(), b.digits.size());
	Num res;
	res.digits.assign(n,0);
	int rem = 0;
	for (int i = 0; i < n; i++) {
		res.digits[i] = get_digit(a.digits,i) + get_digit(b.digits,i) + rem;
		rem = 0;
		while (res.digits[i] >= base) res.digits[i] -= base, ++rem;
	} 
	if (rem > 0) res.digits.push_back(rem);
	return res;
}

Num operator* (const Num& a, const Num& b) {
	const int m = (int) a.digits.size();
	const int n = (int) b.digits.size();
	Num res(0);
	vector<Int> dgs;
	for (int i = 0; i < n; i++) {
		dgs.assign(m+1, 0);
		for (int j = 0; j < m; j++) 
			dgs[j] += (Int) b.digits[i] * a.digits[j],
			dgs[j+1] += dgs[j] / base,
			dgs[j] %= base;
		while (dgs.back() == 0) dgs.pop_back();
		Num add(0);
		for (int k = 0; k < i; k++) add.digits.push_back(0);
		for (auto x : dgs) add.digits.push_back(x);
		res = res + add;
	}
	return res;
}

Num operator- (const Num& a, const Num& b) { //a greater than b
	const int n = a.digits.size();
	Num res; res.digits.assign(n,0);
	int borrow = 0;
	for (int i = 0; i < n; i++) {
		res.digits[i] = a.digits[i] - (get_digit(b.digits,i) + borrow);
		borrow = 0;
		while (res.digits[i] < 0) res.digits[i] += base, borrow++;
	}
	while (res.digits.size() > 1 and !res.digits.back()) res.digits.pop_back();
	return res;
}

pair<Num,Num> operator/ (Num a, const Num& b) {
	vector<Num> pwr, val;
	pwr.push_back(b);
	val.push_back(1);
	while (pwr.back() < a) {
		pwr.push_back(pwr.back() + pwr.back());
		val.push_back(val.back() + val.back());
	}
	Num res;
	auto jt = val.rbegin();
	for (auto it = pwr.rbegin(); it != pwr.rend(); it++, jt++)
		if ((*it) <= a) a = a - (*it), res = res + (*jt);
	return make_pair(res,a);	
}

Int lcm(Int a, Int b) { return ((a /= __gcd(a,b)) *= b); }
Num lcm2(Int a, Int b) {
	return Num(a /= __gcd(a,b)) * Num(b);
}
