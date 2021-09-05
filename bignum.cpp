#include<bits/stdc++.h>
using namespace std;

//typedef unsigned long long Int;
typedef long long Int;
typedef long double Real;

const int MOD = 2004010501; //MOD > 2e9

//Bignum tu viet, pro no phai the
constexpr int base = 1e9;
//void mod_add(int& var, const int& val) { var += val; if (var >= base) var -= base; }
struct Num {
	vector<int> digits;
	Num() { digits.assign(1,0); }
	Num(Int x) {
		digits.clear();
		for (;x; x /= base) digits.push_back(x % base);
	}
	void print() const {
		for (auto it = digits.rbegin(); it != digits.rend(); it++) {
			if (it != digits.rbegin()) {
				int d = 0; for (int tmp = *it; tmp; tmp /= 10) d++;
				if (!d) d ^= 1;
				for(d = 9-d; d --> 0; ) cout << 0;
			}
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
	return (pos < x.size()) ? x[pos] : 0;
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

int main()
{
	#define task "coins"
	if (fopen(task".inp", "r")) {
		freopen(task".inp", "r", stdin);
		freopen(task".out", "w", stdout);
	}

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	if (false)
	{
//		(Num(1e9) - Num()).print();
//		Num a(1e9), b(1e9+1);
//		Num c = a * b;
//		cerr << "Test : "; c.debug(); cerr << '\n';
//		c = c + (a-1);
//		cerr << "Test : "; c.debug(); cerr << '\n';
//		auto divi = c / a;
//		cerr << "Quotient, Rem = "; divi.first.debug(); cerr << " | "; divi.second.debug(); cerr << '\n';
	}
	
	int num_coins, num_types;
//	scanf("%d %d", &num_coins, &num_types);
	cin >> num_coins >> num_types;
	Int thickness[num_coins];
//	for (int i = 0; i < num_coins; i++) scanf("%lld", thickness+i);
	for (int i = 0; i < num_coins; i++) cin >> thickness[i];
	
	vector<Num> big_bases;
	vector<Int> small_bases;
	for (int a = 0; a < num_coins; a++)
		for (int b = a+1; b < num_coins; b++)
			for (int c = b+1; c < num_coins; c++)
				for (int d = c+1; d < num_coins; d++) {
					Num basis = lcm2(lcm(thickness[a],thickness[b]), lcm(thickness[c],thickness[d]));
					if (basis.digits.size() <= 2) 
						small_bases.push_back(lcm(lcm(thickness[a],thickness[b]), lcm(thickness[c],thickness[d])));
					else big_bases.push_back(basis);
				}
//	cout << bases.size() << " wow so many\n";
//	for (auto basis : bases) basis.print(), cout << '\n';
				
	for (Int height; num_types --> 0;) {
//		scanf("%lld", &height);
		cin >> height;
		Num hei(height);
		Num lower, higher;
		higher.digits.assign(4, base-1);
		for (auto basis : big_bases) {
			if (hei < basis) {
				higher = min(higher,basis);
				continue;
			}
			pair<Num,Num> division = hei / basis;
			Num _lower = hei - division.second;
			lower = max(lower, _lower);
			Num _higher = _lower;
			if (division.second.digits.size() > 1 or division.second.digits.front() > 0)
				_higher = _higher + basis;
			higher = min(higher, _higher);
		}
		for (auto basis : small_bases) {
			Int _lower = (height / basis) * basis;
			lower = max(lower, (Num) _lower);
			Int _higher = _lower + (_lower < height ? basis : 0);
			higher = min(higher, (Num) _higher);
		}
		lower.print(); cout << ' '; higher.print(); cout << '\n';
//		cerr << "Finished a testcase\n";
	}
}
