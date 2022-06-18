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

string seed;

int main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);

	freopen("script.txt", "w", stdout);

	int num_tests = 20;
	const int cnt_subs[] {6,7,7};
	
	for (int tid = 1; tid <= num_tests; tid++) {
		int rem = tid;
		int sub = -1;
		for (int i = 0; i < 3; i++)
			if ((rem -= cnt_subs[i]) <= 0) 
				{ sub = i; break; }
		seed.resize(20);
		for (auto& c : seed) c = (char) random('a', 'z');
		assert((sub != -1));
		printf("gen %d %d %s > $\n", sub, tid, seed.c_str());
	}                                      
}
