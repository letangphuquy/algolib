/*
Given two array a & b, each has length n.
Perform 10^6 queries of two types :
1) increase a[l..r] by c : a[l] += c, a[l+1] += c, ..., a[r] += c
2) compute F(l,r) = sigma(a[i] * b[i]) = a[l] * b[l] + a[l+1] * b[l+1] + ... + a[r] * b[r]
*/
struct Node {
	int sum_values, sum_coefs, lazy;
	Node() {};
};
void push_up(Node& x, const Node& L, const Node& R) {
	x.sum_values = L.sum_values + R.sum_values;
}
struct SegmentTree {
	#define mid (l+r>>1)
	int range;
	Node nodes[4 * MAXN];
	void build(int x, int l, int r, const int coefs[]) {
		if (l == r)
			nodes[x].sum_coefs = coefs[r];
		else {
			build(x*2, l, mid, coefs);
			build(x*2+1, mid + 1, r, coefs);
			nodes[x].sum_coefs = nodes[x*2].sum_coefs + nodes[x*2+1].sum_coefs;
		}
		cerr << "[" << l << ',' << r << "] : " << nodes[x].sum_coefs << '\n';
	}
	SegmentTree(int range, const int a[]) : range(range) {
		build(1, 1, range, a);
	}
	void push_down(int x) {
		nodes[x*2].sum_values += nodes[x].lazy * nodes[x*2].sum_coefs;
		nodes[x*2+1].sum_values += nodes[x].lazy * nodes[x*2+1].sum_coefs;
		nodes[x*2].lazy += nodes[x].lazy;
		nodes[x*2+1].lazy += nodes[x].lazy;
		nodes[x].lazy = 0;
	}
	int query(int x, int l, int r, const int& L, const int& R) {
		if (l > R or L > r) return 0;
		if (L <= l and r <= R) return nodes[x].sum_values;
		push_down(x);
		int result = query(x*2, l, mid, L, R) + query(x*2+1, mid+1, r, L, R);
		/*
		Node result;
		push_up(result, query(x*2,l,mid,L,R), query(x*2+1,mid+1,r,L,R);
		*/
		return result;
	}
	void range_update(int x, int l, int r, const int& L, const int& R, const int& delta) {
		if (l > R or L > r) return ;
		if (L <= l and r <= R) {
			nodes[x].sum_values += delta * nodes[x].sum_coefs;
			nodes[x].lazy += delta;
			return;
		}
		push_down(x);
		range_update(x*2, l, mid, L, R, delta);
		range_update(x*2+1, mid+1, r, L, R, delta);
		nodes[x].sum_values = nodes[x*2].sum_values + nodes[x*2+1].sum_values;
	}
	int query(const int& l, const int& r) {
		return query(1, 1, range, l, r);
	}
	void range_update(const int& l, const int& r, const int& delta) {
		range_update(1, 1, range, l, r, delta);
	}
	#undef mid
};
