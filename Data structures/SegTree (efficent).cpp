#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 500;

struct SegTree {
	int range, nodes[2 * MAXN];
	SegTree() {}
	void build(int* a) {
		for (int i = 1; i <= range; i++) nodes[i+range] = a[i];
		for (int i = range; i > 0; i--) nodes[i] = max(nodes[i*2], nodes[i*2+1]);
	}
	SegTree(int range, int* a) : range(range) { build(a); }
	void update(int pos, int val) {
		for (nodes[pos += range] = val; pos > 1; pos >>= 1)  nodes[pos >> 1] = max(nodes[pos], nodes[pos^1]);
	}
	int query(int l, int r) const {
		int res = 0;
		for (l += range, r += range; l <= r; l >>= 1, r >>= 1) {
			if (l&1) res = max(res, nodes[l++]);
			if (r&1); else res = max(res, nodes[r--]);
		}
		return res;
	}
} find_max;
int val[MAXN];

int main()
{
	int num_elems, num_queries;
	scanf("%d %d", &num_elems, &num_queries);
	for (int v = 1; v <= num_elems; v++) scanf("%d", val+v);

	find_max = SegTree(num_elems, val);
	
	for (int t,u,v; num_queries --> 0; ) {
		scanf("%d %d %d", &t, &u, &v);
		if (t == 1) find_max.update(u,v);
		else printf("%d\n", find_max.query(u,v));
	}
}


