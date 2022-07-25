/*
Given two array a & b, each has length n.
Perform 10^6 queries of two types :
1) increase a[l..r] by c : a[l] += c, a[l+1] += c, ..., a[r] += c
2) compute F(l,r) = sigma(a[i] * b[i]) = a[l] * b[l] + a[l+1] * b[l+1] + ... + a[r] * b[r]
*/
const int MAXN = 1e5 + 50;
struct Node {
	int sum_values;
	Node() {};
};
void push_up(Node& x, const Node& L, const Node& R) {
	x.sum_values = L.sum_values + R.sum_values;
}
struct SegmentTree {
	int range;
	int lazy[4 * MAXN]; // thông tin lazy
	int sum_coefs[4 * MAXN]; //thông tin cố định - lưu ở đây
	Node nodes[4 * MAXN];
	void build(int x, int l, int r, const int coefs[]) {
		if (l == r)
			sum_coefs[x] = coefs[r];
		else {
			int m = (l+r)/2;
			build(2*x, l,m, coefs);
			build(2*x+1, m+1,r, coefs);
			sum_coefs[x] = sum_coefs[2*x] + sum_coefs[2*x+1];
		}
		cerr << "[" << l << ',' << r << "] : " << sum_coefs[x] << '\n'; //debug - xóa dòng này
	}
	SegmentTree(int range, const int a[]) : range(range) {
		build(1, 1, range, a);
	}
	void push_down(int x) {
		if (!lazy[x]) return ;
		for (int y = 2*x; y <= 2*x+1; y++) {
			nodes[y].sum_values += lazy[x] * sum_coefs[y];
			lazy[y] += lazy[x];
		}
		lazy[x] = 0;
	}
	int query(int x, int l, int r, const int& L, const int& R) {
		if (l > r or l > R or L > r or L > R) return 0;
		if (L <= l and r <= R) return nodes[x].sum_values;
		int m = (l+r)/2; push_down(x); 
		int result = query(x*2, l,m, L, R) + query(x*2+1, m+1,r, L, R);
		/*
		Node result;
		push_up(result, query(x*2,l,mid,L,R), query(x*2+1,mid+1,r,L,R));
		*/
		return result;
	}
	void range_update(int x, int l, int r, const int& L, const int& R, const int& delta) {
		if (l > r or l > R or L > r or L > R) return ;
		if (L <= l and r <= R) {
			nodes[x].sum_values += delta * sum_coefs[x];
			lazy[x] += delta;
			return;
		}
		int m = (l+r) / 2; push_down(x);
		range_update(2*x, l,m, L, R, delta);
		range_update(2*x+1, m+1,r, L, R, delta);
		nodes[x].sum_values = nodes[2*x].sum_values + nodes[2*x+1].sum_values;
	}
	int query(const int& l, const int& r) {
		return query(1, 1, range, l, r);
	}
	void range_update(const int& l, const int& r, const int& delta) {
		range_update(1, 1, range, l, r, delta);
	}
};
