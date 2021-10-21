/***********************************************************
Given a System of Linear Algebra Equations (SLAE), solve it.
This code implements the modulo version :
c(i,1) * x1 + c(i,2) * x2 + c(i,3) * x3 + ... + c(i,n) * xn = c(i,n+1) (modulo p)
***********************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MOD = 2004010501;
typedef long long Int;

/*problem*/
int num_nodes, num_edges;
vector<set<int>> adj;
vector<Int> capa;
vector<int> init;

bool compare(const int& u, const int& v) { return capa[u] < capa[v]; }
vector<int> node_list;

/*gauss*/
int nvars, base = 3;
struct TEquation {
	int* coefs;
	TEquation() { coefs = new int[nvars+1]; for (int i = 0; i <= nvars; i++) coefs[i] = 0; }
	int& operator[] (const int& i) const { return coefs[i]; }
	int sum(void) const { return coefs[nvars]; }
	TEquation& operator += (const TEquation& other) {
		for (int i = 0; i <= nvars; i++) {
			(coefs[i] += other[i]);
			if (coefs[i] < 0) coefs[i] += base;
			if (coefs[i] >= base) coefs[i] -= base;			
		}
		return *this;
	}
	TEquation& operator *= (const int& multiplier) {
		for (int i = 0; i <= nvars; i++) {
			(coefs[i] *= multiplier) %= base;
			if (coefs[i] < 0) coefs[i] += base;
			if (coefs[i] >= base) coefs[i] -= base;			
		}
		return *this;
	}
};

vector<TEquation> equations;
void show_SLAE() {
	for (int i = 0; i < (int) equations.size(); i++) {
		cerr << "Equation " << i << " : ";
		for (int j = 0; j < nvars; j++) cerr << equations[i][j] << ' ';
		cerr << " = " << equations[i].sum() << "\n";
	}
}

vector<int> solution;
vector<bool> is_fixed;
int modular_inverse(int x) { return x; }
#define INFINITE_SOLUTION -2
#define NO_SOLUTION -1
int gauss_elimination() {
	vector<TEquation> slae(equations);
	const int nequas = slae.size();
	for (int j = 0; j < nvars; j++) solution[j] = -1;
	is_fixed.assign(nequas, false);
	int cnt_vars = 0;
	for (auto j : node_list) {
		bool check = false;
		for (int i = 0; i < nequas; i++) if (!is_fixed[i]) {
			if (slae[i][j] != 0) {
				is_fixed[i] = true;
				solution[j] = i;
				check = true;
				slae[i] *= modular_inverse(slae[i][j]);
				for (int _i = 0; _i < nequas; _i++) if (_i != i and slae[_i][j]) {
					TEquation subtract;
					for (int t = 0; t <= nvars; t++) subtract[t] = slae[i][t];
					slae[_i] += (subtract *= -slae[_i][j]);
				}
				break;
			}
		}
		cnt_vars += !check;
//		cerr << "After phase " << j << '\n';
//		show_SLAE();
	}
	for (int j = 0; j < nvars; j++) 
		if (solution[j] >= 0) {
			int i = solution[j];
			assert(slae[i][j] == 1);
			solution[j] = (slae[i].sum()+base) % base;
		}
		else solution[j] = 0;
	for (int i = 0; i < nequas; i++) {
		int lhs = 0;
		for (int j = 0; j < nvars; j++) (lhs += solution[j] * equations[i][j]) %= base;
		if (lhs < 0) lhs += base;
		if (lhs != equations[i].sum()) {
			cerr << "NO SOLUTION\n";
			return NO_SOLUTION;
		}
	}
	return cnt_vars;
	
}


bool check(int lim) {
	cerr << "AT " << lim << '\n';
	nvars = num_nodes;
	for (int aim = 0; aim < 3; aim++) {
		cerr << "AIM " << aim << '\n';
		equations.clear();
		for (int i = 0; i < num_nodes; i++) {
			const int& u = node_list[i];
			TEquation e_i;
			e_i.coefs[u] = (capa[u] <= capa[node_list[lim]]) ? ((int) adj[u].size() * (-1) + base) % base : 0;
			for (auto v : adj[u]) if (capa[v] <= capa[node_list[lim]])
				(++e_i.coefs[v]) %= base;
			e_i.coefs[num_nodes] = (aim - init[u] + base) % base;
			equations.push_back(e_i);
		}
//		show_SLAE();
		if (gauss_elimination() != NO_SOLUTION) {
//			bool ok = true;
//			for (int i = 0; i < num_nodes; i++)
//				if (capa[i] > capa[node_list[lim]] and solution[i] != 0)
//					ok = false;
			cerr << "AT " << lim << " : ok\n";
			return true;
		}
	}
	cerr << "AT " << lim << " : not ok\n";
	return false;
}

int main()
{ 
    #define task "graph3"
    if (fopen(task".inp", "r")) {
    	freopen(task".inp", "r", stdin);
    	freopen(task".out", "w", stdout);
    }
//    freopen("debug.txt", "w", stderr);
    scanf("%d%d", &num_nodes, &num_edges);
    adj.resize(num_nodes);
    capa.resize(num_nodes);
	init.resize(num_nodes);
    for (int i = 0; i < num_nodes; i++)
    	scanf("%d%lld", &init[i], &capa[i]);
    for (int u,v,i = 0; i < num_edges; i++) 
    	scanf("%d%d", &u, &v),
    	--u, --v,
    	adj[u].insert(v),
    	adj[v].insert(u);
    node_list.resize(num_nodes);
	iota(node_list.begin(), node_list.end(), 0);
	sort(node_list.begin(), node_list.end(), compare);
//	cerr << "NODE LIST : "; for (auto x : node_list) cerr << x << ' '; cerr << '\n';
	solution.resize(num_nodes);
    int lo = 0, hi = num_nodes-1, ans = -1;
    while (lo <= hi) {
    	int mid = lo+hi >> 1;
    	if (check(mid)) ans = mid, hi = mid-1; else lo = mid+1;
	}
	if (ans >= 0) {
		printf("%lld\n", capa[node_list[ans]]);
		check(ans);
		for (int i = 0; i < num_nodes; i++) 
			printf("%d ", solution[i]);
	} else puts("-1");
}


