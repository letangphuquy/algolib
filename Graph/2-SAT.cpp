#include<bits/stdc++.h>
using namespace std;

typedef long long Int;

const int MAX = 2e5 + 500;

int num_nodes; // num_conditions, pr1[MAX], pr2[MAX];
int num_vars;

vector<int> adj[MAX];
void add_arc(int u, int v) {
	adj[u].push_back(v);
}
int NOT(const int& t) { return t^1; }
void VRAI(const int& u) { add_arc(NOT(u),u); }
void FAUX(const int& u) { add_arc(u,NOT(u)); }
void OR(const int& x, const int& y) {
	add_arc(NOT(x), y);
	add_arc(NOT(y), x);
}
void EQUAL(const int& x, const int& y) {
	add_arc(x,y);
	add_arc(y,x);
	add_arc(NOT(x), NOT(y));
	add_arc(NOT(y), NOT(x));
}
void NEQUAL(const int& x, const int& y) { EQUAL(x, NOT(y)); }

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
    num_vars = 2 * num_nodes;
    for (int u = 1; u <= num_vars; u++) 
        adj[u].clear(), 
        comp[u] = ord[u] = low[u] = 0;
    for (int i = 1; i <= num_conditions; i++) 
 	OR(pr1[i], pr2[i]);
    ::num_comps = ::vis_turn = 0;
    for (int u = 0; u < num_vars; u++) 
        if (!ord[u]) tarjan(u);
    for (int u = 0; u < num_vars; u++) {
	ans[u] = comp[NOT(u)] > comp[u];
        if (comp[u] == comp[NOT(u)]) return false;
    }
    return true;
}

int main()
{ 
    /*input*/
    assert(solve());
}


