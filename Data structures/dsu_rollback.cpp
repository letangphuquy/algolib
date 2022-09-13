#include<bits/stdc++.h>
using namespace std;

const int MOD = 2004010501;
typedef long long Int;
typedef long double Real;

#define DBG(x) cerr << #x << " = " << x << ' ';
#define DBGn(x) cerr << #x << " = " << x << '\n';

//https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/A

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

void main() {}
