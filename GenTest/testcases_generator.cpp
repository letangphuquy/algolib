/** Declare here **/
#include<bits/stdc++.h>
#include<thread>
using namespace std;

/* Task's parameters */
const string taskname = "a03";
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
    //cerr << name << "\n";
    return name;
}

typedef long long Int;
typedef long double Real;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
Int random(Int l, Int r) { return uniform_int_distribution<Int>(l,r)(rng); }

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
