class DisjointSet {
private :
	int size; int* label;
public :
	DisjointSet(int size) : size(size) {
		label = new int[size + 1];
	    for (int i = 0; i <= size; i++) label[i] = -1;
  	}
  	
  	int find_root(int u) {
    	if (label[u] < 0) return u;
    	return label[u] = find_root(label[u]);
  	}
  
  	bool merge_set(int u, int v) {
    	u = find_root(u), v = find_root(v);
	    if (u == v) return false;
	    if (-(label[u]) < -(label[v])) swap(u,v);
	    return label[u] += label[v], label[v] = u, true;
  	}
  	
  	bool same_set(int a, int b) { 
    	return find_root(a) == find_root(b);
  	}
};
