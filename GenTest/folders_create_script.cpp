#include<bits/stdc++.h>
using namespace std;

int main()
{
    int num_tests;
    cin >> num_tests;
    freopen("create.cmd", "w", stdout);
    int width = log10(num_tests);
    for (int i = 1; i <= num_tests; i++) {
        int length = log10(i);
        cout << "md Test";
        for (int j = 0; j < width-length; j++) cout << "0";
        cout << i << "\n";
    }
}
