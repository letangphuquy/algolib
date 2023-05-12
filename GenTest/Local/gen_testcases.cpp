#include<bits/stdc++.h>
using namespace std;

/* Task's parameters */
const string taskname = "stgraph";
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

//Pass in more arguments (to both function calls & command line) if needed.
//for example, -flag, --option value (just like testlib.h of CF Polygon)

void generate_input(string fname, vector<string> opts = {}) {
	string command = "gen_input.exe " + fname;
	for (auto opt : opts) command += " " + opt;
    system(command.c_str());
}

void generate_output(string inpname, string outname, vector<string> opts = {}) {
	string command = "gen_output.exe " + inpname + " " + outname;
	for (auto opt : opts) command += " " + opt;
	system(command.c_str());
}

int main()
{
    /**          GENERATE INPUT          **/
    for (int test_id = 1; test_id <= num_tests; test_id++) {
        string fname = getTestName(test_id) + "/" + taskname + inpformat;
		generate_input(fname);
		cerr << "done INP " << test_id << '\n';
    }

    /**          GENERATE OUTPUT          **/
    for (int test_id = 1; test_id <= num_tests; test_id++) {
        string name = getTestName(test_id) + "/" + taskname;
        string inpname = name + inpformat;
        string outname = name + outformat;
		generate_output(inpname, outname);
		cerr << "done OUT " << test_id << '\n';
    }
}

/** Declare here **/
