struct Data {
    Data() {}
    Data operator+ (const Data& rhs) const { return *this; }
};
struct FenwickTree {
    int range; 
    Data* tree;
    FenwickTree() {}
    void resize() { tree = new Data[range+1]; fill(tree, tree+1+range, Data()); } 
    FenwickTree(int range) : range(range) { resize(); }
    void init(int n) { range = n; resize(); }
    void update(int x, const Data& add) { for (;x <= range; x += x&-x) tree[x] = tree[x] + add; }
    Data query(int x) { Data res; for (;x; x &= x-1) res = res + tree[x]; return res; }
};
