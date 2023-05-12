#include<bits/stdc++.h>
using namespace std;

typedef long long Int;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
Int random(Int l, Int r) { return uniform_int_distribution<Int>(l,r)(rng); }
char random_char(void) {
	return (char) random('a', 'z');
}

string random_string(int n = 10) {
	string res;
	while (n-->0) res += random_char();
	return res;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	if (argc > 1) {
		freopen(argv[1], "w", stdout);
		cerr << "Got " << argc << ", generating for " << argv[1] << '\n';
		cout << "hash: " << random_string() << '\n';
	} else {
		cerr << "No argument passed in!";
	}
}