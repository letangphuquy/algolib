#include<bits/stdc++.h>
using namespace std;

const int VERTEX = 1e5;
const int EDGE = 2e5;

int num_nodes, source, sink;

struct EdmondsKarp {
	int E = -1;
	int from[EDGE], to[EDGE], flow[EDGE], capa[EDGE];
	vector<int> network[VERTEX];
	EdmondsKarp() {}
	
	void add_edge(int u, int v, int cap) {
		network[u].push_back(++E);
		from[E] = u, to[E] = v;
		capa[E] = cap, flow[E] = 0;
		
		network[v].push_back(++E);
		from[E] = v, to[E] = u;
		capa[E] = flow[E] = 0; 
	}
	
	#define NONE -1
	int edge[VERTEX]; //edge to parent
	void find_augmenting_path() {
		fill(edge, edge + 1 + num_nodes, NONE);
		edge[source] = 0;
		queue<int> bfs;
		bfs.push(source);
		while (!bfs.empty()) {
			int u = bfs.front(); bfs.pop();
			for (int i : network[u]) 
				if (flow[i] < capa[i] and edge[to[i]] == NONE)
					edge[to[i]] = i, bfs.push(to[i]);
		}
	}
	
	const int INF = 1e9;
	int maxflow() {
		int result = 0;
		do {
			find_augmenting_path();
			if (edge[sink] == NONE) return result;
			int bottleneck = INF;
			for (int u = sink; u != source; u = from[edge[u]])
				bottleneck = min(bottleneck, capa[edge[u]] - flow[edge[u]]);
			result += bottleneck;
			for (int u = sink; u != source; u = from[edge[u]])
				flow[edge[u]] += bottleneck,
				flow[edge[u] ^ 1] -= bottleneck;
		} while (true);
		return INF;
	}
};

int main()
{
}


