#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, (int) 5e5, "n");
    inf.readSpace();
    int k = inf.readInt(1, (int) 1e9, "k");
    inf.readEoln();
    
    inf.readInts(n, 0, (int) 1e9, "a_i");
    inf.readEoln();

    inf.readEof();
}
