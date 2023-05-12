const int MOD = 1e9 + 7;
typedef long long Int;
void add(int &a, const int& b) { 
	if ((a+=b) >= MOD) a -= MOD; 
	if (a < 0) a += MOD;
}
int product(const int& a, const int& b) { return (Int)a*b % MOD; }

int pwr_mod(int a, int n) {
	if (!n) return 1;
	return product(pwr_mod(product(a,a), n/2), (n%2) ? a : 1);
}

const int N = 1e6 + 100;
int fac[N], inv[N];
void prepare(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = product(fac[i-1], i);
	inv[n] = pwr_mod(fac[n], MOD-2);
	for (int i = n-1; i >= 0; i--) inv[i] = product(inv[i+1], i+1);
}
int combi(int n, int k) {
	return product(fac[n], product(inv[k], inv[n-k]));
}
