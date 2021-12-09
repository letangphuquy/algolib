struct Data {
    Data() {}
    Data operator+ (const Data& rhs) const { return *this; }
};
template<typename T> struct FenwickTree {
	bool get_prefix;
    int range; T* tree;
    FenwickTree() {}
	void reset() { fill(tree, tree+1+range, T()); }
    void resize() { tree = new T[range+1]; reset(); }
    FenwickTree(int range, bool get_prefix) : range(range), get_prefix(get_prefix) { resize(); }
    void init(int n, bool b) { range = n; get_prefix = b; resize(); }
    void update(int x, const T& add) {
		if (get_prefix) for (;x <= range; x += x&-x) tree[x] = tree[x] + add;
   		else for (;x; x &= x-1) tree[x] = tree[x] + add;
	}
    T query(int x) {
		T rex;
		if (get_prefix) for (;x; x &= x-1) rex = rex + tree[x];
		else for (;x <= range; x += x&-x) rex = rex + tree[x];
		return rex;
	}
};
