/***********************************************************
Given a System of Linear Algebra Equations (SLAE), solve it.
This code implements the modulo version :
c(i,1) * x1 + c(i,2) * x2 + c(i,3) * x3 + ... + c(i,n) * xn = c(i,n+1) (modulo p)
***********************************************************/

#include<bits/stdc++.h>
using namespace std;

int nvars, base;
struct TEquation {
	int* coefs;
	TEquation() { coefs = new int[nvars+1]; memset(coefs, 0, sizeof(coefs)); }
	const int operator[] (const int& i) const { return coefs[i]; }
	const int sum(void) const { return coefs[nvars]; }
	TEquation& operator += (const TEquation& other) {
		for (int i = 0; i <= nvars; i++) (coefs[i] += other[i]) %= base;
		return *this;
	}
	TEquation& operator *= (const int& multiplier) {
		for (int i = 0; i <= nvars; i++) (coefs[i] *= multiplier) %= base;
		return *this;
	}
};

vector<TEquation> equations;
void show_SLAE() {
	for (int i = 0; i < equations.size(); i++) {
		cerr << "Equation " << i << " : ";
		for (int j = 0; j < nvars; j++) cerr << equations[i][j] << ' ';
		cerr << " = " << equations[i].sum() << "\n";
	}
}

int modular_inverse(int x, int p) { return (x == 1) ? 1 : 2;} //todo

#define INFINITE_SOLUTION -2
#define NO_SOLUTION -1
int gauss_elimination() {
	const int nequas = equations.size();
	int cnt_vars = 0;
	vector<int> sol(nvars, -1);
	for (int i = 0; i < nequas; i++) {
		bool check = false;
		cerr << "considering " << i << '\n';
		for (int j = 0; j + 1 < nvars; j++) {
			if (equations[i][j] != 0) {
				cerr << "found var " << j << '\n';
				check = true;
				for (int _i = 0; _i < nequas; _i++) if (_i != i and equations[_i][j]) {
					int c = modular_inverse(equations[i][j], base) * equations[_i][j] % base;
					cerr << "coef = " << c << "->";
					equations[_i] += (equations[i] *= -c);
					c = modular_inverse(c, base);
					equations[i] *= -c;
					cerr << "Neutralized " << _i << '\n';
				}
				break;
			}
		}
		if (!check and equations[i].sum() != 0) return NO_SOLUTION;
		cnt_vars += !check;
		cerr << "After phase " << i << '\n';
		show_SLAE();
	}
	return cnt_vars;
	
}

int main()
{
	freopen("debug.txt", "w", stderr);
	cout << "Please input number of varriables, and the modulo\n";
	cin >> nvars >> base;
	int nequas;
	cout << "Input the number of equations\n";
	cin >> nequas;
	for (;nequas --> 0;) {
		TEquation eq;
		for (int i = 0; i <= nvars; i++) cin >> eq.coefs[i];
		equations.push_back(eq);
	}
	cout << gauss_elimination();
}
