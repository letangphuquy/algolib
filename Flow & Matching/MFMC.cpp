#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
typedef long double Real;

const int MOD = 2004010501; //MOD > 2e9

const int INF = 1e9;
const int VERTEX = 1e5 + 500;
const int EDGE = 1e5 + 500;

struct MinimumCost {
	int source, sink;
	int V = 0, E = -1;
	vector<int> network[VERTEX];
	int from[EDGE], to[EDGE], flow[EDGE], capa[EDGE], cost[EDGE];
	
	MinimumCost() {}
	
	void add_arc(int u, int v, int Capa, int Cost) {
		network[u].push_back(++E);
		from[E] = u, to[E] = v;
		cost[E] = Cost;
		capa[E] = Capa, flow[E] = 0;
		
		network[v].push_back(++E);
		from[E] = v, to[E] = u;
		cost[E] = Cost * (-1);
		capa[E] = flow[E] = 0; 
	}
	
	int dist[VERTEX], par_edge[VERTEX];
	bool inq[VERTEX];
	bool found_shortest_augmenting_path() { //ford-bellman improved
		fill(dist, dist + 1 + V, -INF);
		queue<int> spfa;
		spfa.push(source);
		dist[source] = 0;
		inq[source] = true;
		while (!spfa.empty()) {
			int u = spfa.front(); spfa.pop();
			inq[u] = false;
			for (int& i : network[u]) if (flow[i] < capa[i]) {
				int relax = dist[u] + cost[i];
				if (relax > dist[to[i]]) {
					par_edge[to[i]] = i;
					dist[to[i]] = relax;
					if (!inq[to[i]]) 
						spfa.push(to[i]), inq[to[i]] = true;
				}				
			}
		}
		return (dist[sink] > -INF);
	}
	
	int compute(int flow_cap = INF) {
		int cost = 0, total_flow = 0;
		do {
			if (!found_shortest_augmenting_path()) break;
			int add = flow_cap - total_flow;
			for (int cur = sink, id; cur != source; cur = from[id]) {
				id = par_edge[cur];
				add = min(add, capa[id] - flow[id]);
			}
			cost += add * dist[sink];
			total_flow += add;
			for (int cur = sink, id; cur != source; cur = from[id]) {
				id = par_edge[cur];
				flow[id] += add;
				flow[id ^ 1] -= add;
			}
		} while (total_flow < flow_cap);
		return (flow_cap < INF and total_flow < flow_cap) ? INF : cost;
	}
};

int main()
{
}


