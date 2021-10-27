const int MOD = 1e9 + 7;
typedef long long Int;

int pwr_mod(int a, int n) {
	if (!n) return 1;
	int res = pwr_mod(a,n/2);
	res = ((Int) res*res) % MOD;
	if (n&1) res = ((Int) res*a) % MOD;
	return res;
}
const int N = 1e6 + 100;
int fac[N], inv[N];
void prepare(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = ((Int) i * fac[i-1]) % MOD;
	inv[n] = pwr_mod(fac[n], MOD-2);
	for (int i = n-1; i >= 0; i--) inv[i] = ((Int) (i+1) * inv[i+1]) % MOD;
}
int combi(int n, int k) {
	return ((Int) fac[n] * (((Int) inv[k] * inv[n-k]) % MOD)) % MOD;
}
