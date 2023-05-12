#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include<bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define cst(T) const T&

template<class A, class B> bool umin(A& var, cst(B) val) {
	return (val < var) ? (var = val, true) : false;
}
template<class A, class B> bool umax(A& var, cst(B) val) {
	return (var < val) ? (var = val, true) : false;
}

typedef long long Int;
typedef long double Real;
const int MOD = 2004010501;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class X, class Y> Int random(const X& l, const Y& r) {
	return uniform_int_distribution<Int>(l,r)(rng);
}
#define DBG(x) cerr << #x << " = " << x << ' ';
#define DBGn(x) cerr << #x << " = " << x << '\n';

template<typename T> vector<T> readInput(int n) {
	vector<T> v(n); for (auto &vi : v) cin >> vi; return v;
}

//Declaration
const int N = 1e5 + 50;

//Change the solve function only (can copy-paste)
void solve(int testID) {
	DBGn(testID);
	string s;
	getline(cin, s);
	cout << "the content\n" << s + s << '\n';
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	if (argc > 2) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
		cerr << "Got " << argc << ", generating for " << argv[2] << '\n';

		int numTests = 1;
		// cin >> numTests;
		for (int i = 1; i <= numTests; i++) solve(i);
	} else {
		cerr << "No argument passed in!";
	}
}