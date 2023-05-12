int numNodes;
vector<pair<int, Int>> adj[N];
vector<Int> dijkstra(int start) {
    //SSSP. Global parameters: adj[][] (pairs), numNodes
    vector<Int> label(numNodes+1, INF);
    struct State {
        int node; Int weight;
        State(int node, Int weight) : node(node), weight(weight) {}
        bool operator< (const State& rhs) const {
            return weight > rhs.weight;
        }
    };
    priority<State> heap;
    label[start] = 0;
    heap.push(State(start,0));
    while (!heap.empty()) {
        auto [u,wu] = heap.top(); heap.pop();
        if (wu != label[u]) continue;
        for (auto [v,we] : adj[u]) 
            if (umin(label[v], label[u] + we))
                heap.push(State(v, label[v]));
    }
    return label;
}