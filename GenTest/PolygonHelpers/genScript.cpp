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

	int numTests = 100;
	const int NUM_SUBTASKS = 3;
	const Real ratio[] = {0.2, 0.3, 0.5};
	int cntTests[NUM_SUBTASKS];
	for (int i = 0; i < NUM_SUBTASKS; i++) {
		cntTests[i] = round(numTests * ratio[i]);
		DBGn(cntTests[i]);
	}
	for (int tid = 1; tid <= numTests; tid++) {
		int rem = tid, sub = -1, tot = 0;
		for (int i = 0; i < NUM_SUBTASKS; i++)
			if ((rem -= cntTests[i]) <= 0) { 
				sub = i; rem += (tot = cntTests[i]); break; 
			}
		//rem: test order
		seed.resize(20);
		for (auto& c : seed) c = (char) random('a', 'z');
		assert((sub != -1));
		printf("gen %d %d %d %s > $\n", sub, tot, rem, seed.c_str());
	}                                      
}
