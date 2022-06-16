#include<bits/stdc++.h>
using namespace std;

const int MOD = 2004010501;
typedef long long Int;
typedef long double Real;

#define DBG(x) cerr << #x << " = " << x << ' ';
#define DBGn(x) cerr << #x << " = " << x << '\n';

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
Int random(const Int& l, const Int& r) {
	return uniform_int_distribution<Int>(l,r)(rng);
}
template<class A, class B>
	void maximize(A& var, const B& val) { if (val > var) var = val; }
template<class A, class B>
	void minimize(A& var, const B& val) { if (val < var) var = val; }

int main()
{
	freopen("doall.bat", "r", stdin);
	freopen("_doall.bat", "w", stdout);
	
	string s;
	while (getline(cin,s)) {
		if (s.find("input") != string::npos) {
			auto pos = s.find("tests");
			pos += 6; //including slash
			while (isdigit(s[pos])) ++pos;
			s.insert(pos, ".inp");
		} else
		if (s.find("answer") != string::npos) {
			auto pos = s.find("tests");
			pos += 6; //including slash
			while (isdigit(s[pos])) ++pos;
			s.insert(pos, ".inp");
			
			pos = s.find("tests", pos);
			pos += 6; //including slash
			while (isdigit(s[pos])) ++pos;
			s.erase(pos,2); //delete ".a"
			s.insert(pos, ".out");
		}
		cout << s << '\n';
	}
}
