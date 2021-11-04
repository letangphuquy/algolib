#include<bits/stdc++.h>
using namespace std;

typedef long long Int;

const int MAX = 2e5 + 500;

int num_nodes, num_conditions, pr1[MAX], pr2[MAX];

int NOT(const int& t) { if (t > num_nodes) return t-num_nodes; return t+num_nodes; }
vector<int> adj[MAX];
void equal(const int& x, const int& y) {
	adj[x].push_back(y);
	adj[y].push_back(x);
	adj[NOT(x)].push_back(NOT(y));
	adj[NOT(y)].push_back(NOT(x));
}
void nequal(const int& x, const int& y) { equal(x, NOT(y)); }

int ord[MAX], low[MAX], vis_turn = 0;
int num_comps = 0, comp[MAX]; 
stack<int> near;

void tarjan(int u) {
	low[u] = ord[u] = ++vis_turn;
	near.push(u);
	for (auto v : adj[u]) if (!comp[v]) {
		if (!ord[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else low[u] = min(low[u], ord[v]);
	}	
	if (ord[u] == low[u]) {
		++num_comps;
		while (!near.empty()) {
			int v = near.top(); near.pop();
			comp[v] = num_comps;
			if (v == u) break;
		}
	}
}

bool ans[MAX];
bool solve()
{
    for (int u = 1; u <= 2*num_nodes; u++) 
        adj[u].clear(), 
        comp[u] = ord[u] = low[u] = 0;
    for (int i = 1; i <= num_conditions; i++) 
        nequal(pr1[i], pr2[i]);
    ::num_comps = ::vis_turn = 0;
    for (int u = 1; u <= 2*num_nodes; u++) 
        if (!ord[u]) tarjan(u);
    for (int u = 1; u <= num_nodes; u++) 
        if (comp[u] == comp[NOT(u)]) return false;
    return true;
}

int main()
{ 
    /*input*/
    assert(solve());
}


