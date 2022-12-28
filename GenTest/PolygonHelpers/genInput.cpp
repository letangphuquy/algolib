#include "testlib.h"
//Upload as gen.cpp
#include <bits/stdc++.h>
using namespace std;
 
#define all(v) (v).begin(), v.end()
#define sz(v) ((int) v.size())
typedef long double Real;

int sub, tot, ord; //subtask, total test count, order

const int lboundsN[] = {1,   101,     200'000};
const int uboundsN[] = {100, 500'000, 500'000};

int uniformDistribution(const int lb[], const int ub[], int delta = 0) {
    static Real part = (Real) (ub[sub] - lb[sub]) / tot;
    return part * ord + lb[sub] + rnd.next(-delta,0);
}

int maximumInput(int ub[], int delta = 0) {
	return ub[sub] - rnd.next(0,delta);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
 
    sub = atoi(argv[1]);
    tot = atoi(argv[2]);
    ord = atoi(argv[3]);

    int n = uniformDistribution(lboundsN, uboundsN, 3);
    int k = rnd.next(2e6, 1e9);
    cout << n << ' ' << k << '\n';
    //generate sequence - main logic
	for (int i = 1; i <= n; i++)
		cout << rnd.next(0, 1e9) << ' ';
	cout << '\n';
}
