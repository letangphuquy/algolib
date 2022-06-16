#include<bits/stdc++.h>
using namespace std;

const int MOD = 2004010501;
typedef long long Int;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
Int random(const Int& l, const Int& r) {
	return uniform_int_distribution<Int>(l,r)(rng);
}

int main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);

	freopen("script.txt", "w", stdout);

	int num_tests = 20;
	const int cnt_subs[] {10, 10};
	
	for (int tid = 1; tid <= num_tests; tid++) {
		int rem = tid;
		int sub = -1;
		for (int i = 0; i < 2; i++)
			if ((rem -= cnt_subs[i]) <= 0) 
				{ sub = i; break; }
		assert((sub != -1));
		printf("gen %d %d > $\n", sub, tid);
	}                                      
}
