#include<bits/stdc++.h>
using namespace std;

const int MOD = 2004010501;
typedef long long Int;
typedef long double Real;

#define DBG(x) cerr << #x << " = " << x << ' ';
#define DBGn(x) cerr << #x << " = " << x << '\n';

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
Int random(const Int& l, const Int& r) {
	return uniform_int_distribution<Int>(l,r)(rng);
}
template<class A, class B>
	void maximize(A& var, const B& val) { if (val > var) var = val; }
template<class A, class B>
	void minimize(A& var, const B& val) { if (val < var) var = val; }

class DSU_rollback {
private :
	int timer;
	int num_components;
	vector<int> label;
	struct Event {
		int* variable; int value, Time;
		Event(int* variable, int value, int Time) :
			variable(variable), value(value), Time(Time) {
			}
		void undo(void) { *variable = value; }
	};
	vector<Event> changes;
	vector<int> checkpoints;
public :
	DSU_rollback() { 
		label.clear(); 
		changes.clear();
		checkpoints.clear();
	}
	void init(int sz) {
		timer = 0;
		num_components = sz;
		label.assign(sz+1, -1);
	}

	int find_root(int u) {
		if (label[u] < 0) return u;
		return find_root(label[u]); //no path compression heuristics
	}
	
	void assign(int* var, const int& val) {
		++timer;
		changes.push_back(Event(var, *var, timer));
		*var = val;
	}
	
	void query(void) const {
		cout << num_components << '\n';
	}
	
	void unite(int u, int v) {
		u = find_root(u), v = find_root(v);
		if (u == v) {
			query();
			return;
		}
		if (-label[u] < -label[v]) swap(u,v);
		assign(&label[u], label[u]+label[v]);
		assign(&label[v], u);
		assign(&num_components, num_components-1);
		query();
	}
	
	void persist(void) {
		checkpoints.push_back(timer);
	}

	void rollback(void) {
		assert((!checkpoints.empty()));
		int Time = checkpoints.back();
		while (!changes.empty() && changes.back().Time > Time) {
			changes.back().undo();
			changes.pop_back();
		}
		checkpoints.pop_back();
		query();
	}
} dsu;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	{
		cerr << "TESTING POINTER\n";
		typedef pair<int*,int> Event;
		int val = -1;
		Event ev = make_pair(&val, val);
		val = 0;
		cerr << "After change: "; DBGn(val);
		*ev.first = ev.second;
		cerr << "After rollback: "; DBGn(val);
	}
	int n,m;
	cin >> n >> m;
	dsu.init(n);
	while (m --> 0) {
		string typ; cin >> typ;
		if (typ == "union") {
			int u,v; cin >> u >> v;
			dsu.unite(u,v);
		} else 
		if (typ == "persist")
			dsu.persist();
		else
			dsu.rollback();
	}
}