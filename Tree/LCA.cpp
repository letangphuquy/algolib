
const int LG = 18;
const int N = 2e5 + 5;

vector<int> adj[N];
int anc[LG+1][N], depth[N];
#define pa anc[0]
void dfs(int u) {
	depth[u] = depth[anc[0][u]] + 1;
	for (int t = 1; t <= LG; t++)
		anc[t][u] = anc[t-1][anc[t-1][u]];
	for (auto v : adj[u]) if (anc[0][u] != v)
		anc[0][v] = u, dfs(v);
}

int lca(int u, int v) {
	if (depth[u] > depth[v]) swap(u,v);
	for (int dif = depth[v]-depth[u], t = 0; dif; dif /= 2, t++)
		if (dif&1) v = anc[t][v];
	if (u == v) return u;
	for (int t = LG, uu, vv; t >= 0; t--)
		if (uu = anc[t][u], vv = anc[t][v], uu != vv)
			u = uu, v = vv;
	u = anc[0][u];
	return u;
}

int dist(int u, int v) { return depth[u] + depth[v] - 2*depth[lca(u,v)]; }
