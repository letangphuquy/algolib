#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 500;
int num_nodes, root = 1;
vector<int> adj[MAXN];

int parent[MAXN], depth[MAXN], siz[MAXN];
void dfs_size(int u) {
	siz[u] = 1;
	for (int& v : adj[u]) {
		parent[v] = u; depth[v] = depth[u] + 1;
		adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
		dfs_size(v); siz[u] += siz[v];
		if (siz[v] > siz[adj[u][0]]) swap(adj[u][0], v);
	}
}

int head[MAXN], pos[MAXN], timer = 0;
void decompose(int u, bool is_head) {
	pos[u] = ++timer;
	head[u] = is_head ? u : head[parent[u]];
	for (int& v : adj[u]) decompose(v, v != adj[u][0]);
}

struct SegTree { //new style
	int range, Xor[2 * MAXN];
	SegTree() {}
	void build(int* a) {
		for (int i = 1; i <= range; i++) Xor[i+range] = a[i];
		for (int i = range; i > 0; i--) Xor[i] = Xor[2*i] ^ Xor[2*i+1];
	}
	SegTree(int range, int* a) : range(range) { build(a); }
	void update(int pos, int new_val) {
		Xor[pos += range] = new_val;
		for (; pos > 0; pos >>= 1) Xor[pos >> 1] = Xor[pos] ^ Xor[pos ^ 1];
	}
	int query(int l, int r) {
		int res = 0;
		for (l += range, r += range; l <= r; l /= 2, r /= 2) {
			if ((l&1)) res ^= Xor[l++];
			if ((r&1) == 0) res ^= Xor[r--];
		}
		return res;
	}
} solver;

int val[MAXN], real_val[MAXN];

int path_query(int u, int v) {
	int res = 0;
	for (; head[u] != head[v]; v = parent[head[v]]) {
		if (depth[head[u]] > depth[head[v]]) swap(u,v);
		res ^= solver.query(pos[head[v]], pos[v]);
	}
	if (depth[u] > depth[v]) swap(u,v);
	res ^= solver.query(pos[u], pos[v]);
	return res;
}

int main()
{
	#define task "cowland"
	if (fopen(task".in", "r")) {
		freopen(task".in", "r", stdin);
		freopen(task".out", "w", stdout);
	}
	int num_queries;
	scanf("%d %d", &num_nodes, &num_queries);
	for (int u = 1; u <= num_nodes; u++) scanf("%d", val+u);
	for (int u,v, i = 1; i < num_nodes; i++) 
		scanf("%d %d", &u, &v),
		adj[u].push_back(v), adj[v].push_back(u);
		
	depth[root] = 0, 
	dfs_size(root);
	decompose(root , true);
	parent[root] = root;
		
	for (int u = 1; u <= num_nodes; u++) real_val[pos[u]] = val[u];
	solver = SegTree(num_nodes, real_val);
		
	for (int t,a,b; num_queries --> 0; ) {
		scanf("%d %d %d", &t, &a, &b);
		if (t == 1) solver.update(pos[a], b);
		else printf("%d\n", path_query(a,b));
	}
}

