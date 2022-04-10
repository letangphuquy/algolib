//array a, length n, size limit = N
const int N = 1e6;
const int LG = 20;

int n, a[N];
int Min[LG+1][N], POW[LG+1], LOG[N];
void build_sparse_table() {
	for (int i = 1; i <= n; i++) Min[0][i] = a[i];
	POW[0] = 1;
	for (int t = 1; t <= LG; t++) {
		POW[t] = 2*POW[t-1];
		if (POW[t] > n) continue;
		LOG[POW[t]] = t;
		for (int i = 1, j = POW[t], k = j/2+1; j <= n; i++, j++, k++)
			Min[t][i] = min(Min[t-1][i], Min[t-1][k]);
	}
	for (int v = 3; v <= n; v++)
		maximize(LOG[v], LOG[v-1]);
}
int get_min(int l, int r) {
	int d = LOG[r-l+1];
	return min(Min[d][l], Min[d][r-POW[d]+1]);
}
