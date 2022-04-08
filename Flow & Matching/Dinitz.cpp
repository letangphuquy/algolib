#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int VERTEX = 1e5 + 500;
const int EDGE = 1e5 + 500;

struct Dinitz {
	int source, sink;
	int V = 0, E = -1;
	vector<int> network[VERTEX];
	Dinitz() {}
	Dinitz(int source, int sink) : source(source), sink(sink) {}
	void reset_network() {
		E = -1; 
		for (int i = 0; i <= V; i++) network[i].clear(); 
	}
	int from[EDGE], to[EDGE], flow[EDGE], capa[EDGE];
	int add_arc(int u, int v, int cap) {
		network[u].push_back(++E);
		from[E] = u, to[E] = v;
		capa[E] = cap, flow[E] = 0;
		
		network[v].push_back(++E);
		from[E] = v, to[E] = u;
		capa[E] = flow[E] = 0; 
		return E-1;
	}
	bool is_saturated(int e) { return flow[e] == capa[e]; }
 	
	#define NONE -1
	int level[VERTEX];
	bool found_augmenting_path() {
		fill(level, level + 1 + V, NONE);
		level[source] = 0;
		queue<int> bfs;
		bfs.push(source);
		while (!bfs.empty()) {
			int u = bfs.front(); bfs.pop();
			for (int& i : network[u]) 
				if (flow[i] < capa[i] and level[to[i]] == NONE)
					level[to[i]] = level[u] + 1, bfs.push(to[i]);
		}
		return (level[sink] != NONE);
	}
	
	int ptr[VERTEX];
	int blocking_flow(int u, int pushed) {
		if (!pushed or u == sink) return pushed;
		for (int& it = ptr[u]; it < (int) network[u].size(); it++) {
			int id = network[u][it];
			if (level[to[id]] != level[u] + 1 or flow[id] >= capa[id]) continue;
			int amount = min(pushed, capa[id] - flow[id]);
			amount = min(amount, blocking_flow(to[id], amount));
			if (!amount) continue;
			return flow[id] += amount, flow[id ^ 1] -= amount, amount;
		}
		return 0;
	}
	
	int max_flow() {
		int total_flow = 0;
		do {
			if (!found_augmenting_path()) return total_flow;
			fill(ptr, ptr + 1 + V, 0);
			while (int get = blocking_flow(source, INF))
				total_flow += get;
		} while (true);
		return total_flow;
	}
};

int main()
{
	cerr << "hello there\n";
}


