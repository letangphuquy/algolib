/** Declare here **/
#include<bits/stdc++.h>
#include<thread>
using namespace std;

/* Task's parameters */
const string taskname = "";
const string inpformat = ".inp";
const string outformat = ".out";

const int num_tests = 20;
const int width = log10(num_tests)+1;

/* Test cases generating template*/
string getTestName(int id, int w = ::width) {
    int digits[10], n = 0;
    int x = id;
    while (x) digits[n++] = (x%10), x /= 10;
    reverse(digits, digits+n);
    string name = "Test";
    for (int i=0; i<w-n; i++) name += '0';
    for (int i=0; i<n; i++) name += '0' + digits[i];
    return name;
}

/*Utilities & QoL randomization*/
typedef long long Int;
typedef long double Real;

template<class A, class B>
	void maximize(A& var, const B& val) { if (val > var) var = val; }
template<class A, class B>
	void minimize(A& var, const B& val) { if (val < var) var = val; }
#define MAX(a,b) (((a)>(b)) ? (a) : (b))
#define MIN(a,b) (((a)<(b)) ? (a) : (b))

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
Int random(Int l, Int r) { return uniform_int_distribution<Int>(l,r)(rng); }
char random_char(void) {
	return (char) random('a', 'z');
}
template<typename T> 
	T random_element(const vector<T>& v) {
		return v[random(0, (int) v.size()-1)];
	}

template<typename T> 
	void permute(vector<T>& v) {
		shuffle(v.begin(), v.end(), rng);
	}

vector<int> array_starts_from(int n, int s) {
	vector<int> v(n);
	iota(v.begin(), v.end(), s);
	return v;
}

vector<int> identity_permutation(int n) {
	return array_starts_from(n,1);
}

vector<int> random_permutation(int n) {
	auto res = identity_permutation(n);
	permute(res);
	return res;
}

vector<int> random_array_with_sum(int n, int s) {
	vector<int> a(n,0);
	while (s --> 0) a[random(0,n-1)]++;
	return a;
}

class Tree {
private:
	int num_nodes;
	vector<vector<int>> adj;
	Tree() {
		num_nodes = 0;
		adj.clear();
	}
public:
	void init(int n) {
		num_nodes = n;
		adj.resize(n+1);
	}
	void build_tree(int n) {
		init(n);
		vector<int> labels = random_permutation();
		for (int v = 1; v < n; v++) {
			int u = random(0, i-1);
			adj[labels[u]].push_back(labels[v]);
		}
	}
};

class Graph: Tree {
	//TODO
}
/* Problems's variables, procedures and functions (previously-declared) */
const int MAX = 1e5 + 500;
const int INF = 1e9;
const int MOD = 2004010501;

int n;

void generate_input() {
	n = random(1,1e9);
	printf("%d", n);
}

void generate_output() {
	scanf("%d", &n);
	printf("%d", n+1);
}

int main()
{
    /**          GENERATE INPUT          **/
    for (int test_id = 1; test_id <= num_tests; test_id++) {
        string name = getTestName(test_id);
        name += "/";
        name += taskname;
        name += inpformat;
        freopen(name.c_str(), "w", stdout);
		generate_input();
    }

    /**          GENERATE OUTPUT          **/
    for (int test_id = 1; test_id <= num_tests; test_id++) {
        string name = getTestName(test_id) + "/" + taskname;
        string inpname = name + inpformat;
        string outname = name + outformat;
        freopen(inpname.c_str(), "r",  stdin);
        freopen(outname.c_str(), "w", stdout);
		generate_output();
    }
}

/** Declare here **/
