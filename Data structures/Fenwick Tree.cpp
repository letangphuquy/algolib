struct Data {
    Data() {}
    Data operator+ (const Data& rhs) const { return *this; }
};
template<typename T> struct FenwickTree {
    int range;
    T* tree;
    FenwickTree() {}
    void resize() { tree = new T[range+1]; fill(tree, tree+1+range, T()); }
    FenwickTree(int range) : range(range) { resize(); }
    void init(int n) { range = n; resize(); }
    void update(int x, const T& add) { for (;x <= range; x += x&-x) tree[x] = tree[x] + add; }
    T query(int x) { T rex; for (;x; x &= x-1) rex = rex + tree[x]; return rex; }
};
