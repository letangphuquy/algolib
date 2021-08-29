/*Disjoint-Set Unions*/
class DSU {
private :
  int size;
  int* label;
  
  int find_root(int u) const {
    if (label[u] < 0) return u;
    return label[u] = find_root(label[u]);
  }
  
  bool merge_set(int u, int v) {
    u = find_root(u), v = find_root(v);
    if (u == v) return false;
    if (-(label[u]) < -(label[v]) swap(u,v);
    return label[u] += label[v], label[v] = u, true;
  }
public :
  DSU(int size) : size(size) {
    label = new int[size];
    memset(label, -1, sizeof(label));
  }
  bool join(int a, int b) { 
    return merge_set(u,v);
  }
};
