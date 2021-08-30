#include<bits/stdc++.h>
#include<thread>
using namespace std;

/* Task's parameters */
const string taskname = "";
const string inpformat = ".inp";
const string outformat = ".out";

const int num_tests = 100;
const int width = log10(num_tests)+1;

/* Test cases generating template*/
string getTestName(int id, int w = ::width) {
    int digits[10], n = 0;
    int x = id;
    while (x) digits[n++] = (x%10), x /= 10;
    reverse(digits, digits+n);
    string name = "Test";
    int len=0;
    for (int i=0; i<w-n; i++) name += '0';
    for (int i=0; i<n; i++) name += '0' + digits[i];
    //cerr << name << "\n";
    return name;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int random(int l, int r) { return l + uniform_int_distribution<int>(0,r-l)(rng); }

/* Problems's variables, procedures and functions (previously-declared) */
const int MAX = 1e5 + 500;
const int INF = 1e9;
const int MOD = 2004010501;

int n;

void generate_input() {
	  n = 1e5;
	  cout << n << '\n';
}

void generate_output() {
	  cin >> n;
	  cout << n + 1 << '\n';
}

int main()
{
    /**          GENERATE INPUT          **/
    for (int test_id = 1; test_id <= num_tests; test_id++) {
        string name = getTestName(test_id);
        name += "/";
        name += taskname;
        name += inpformat;
        char * file = new char [name.length()+1];
        strcpy(file, name.c_str());
        freopen(file, "w", stdout);
		    generate_input();
    }

    /**          GENERATE OUTPUT          **/
    for (int test_id = 1; test_id <= num_tests; test_id++) {
        string inpname = getTestName(test_id);
        inpname += "/";
        inpname += taskname;
        string outname = inpname + outformat;
        inpname += inpformat;
        char * inpfile = new char [inpname.length()+1];
        strcpy(inpfile, inpname.c_str());
        char * outfile = new char [outname.length()+1];
        strcpy(outfile, outname.c_str());
        freopen(inpfile, "r",  stdin);
        freopen(outfile, "w", stdout);
		    generate_output();
        cout.flush();
    }
}

/** Declare here **/
