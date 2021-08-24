#include<bits/stdc++.h>
using namespace std;
//https://lqdoj.edu.vn/problem/3d17bomb
const int N = 35;
int nrows, ncols, board[N][N];
int get_index(int i, int j) {//coordinate : 1-indexed, get_index : 0-indexed
	return (i - 1) * ncols + j - 1; //therefore, highest index = nrows * ncols - 1
}
void get_coordinate(int idx) {
	cerr << "(" << (idx / ncols) + 1 << " " << (idx % ncols) + 1 << ") "; 
}

int nvars;
const int base = 2;
struct TEquation {
	vector<int> coefs; //including : say, free coefficent
	TEquation() { coefs = vector<int>(nvars + 1, 0); }
	void operator-= (const TEquation& other) {
		for (int i = 0; i <= nvars; i++) 
			(this -> coefs[i] += base - other.coefs[i]) %= base;
	}
	void operator*= (const int& multiplier) {
		for (int i = 0; i <= nvars; i++) 
			(this -> coefs[i] *= multiplier) %= base;
	}
};
//SPECIAL CASE : 
vector<TEquation> equations;
void show_SLAE() {
	for (int i = 0; i < equations.size(); i++) {
		cerr << "Equation " << i << " : ";
		for (int j = 0; j < nvars; j++) 
			if (equations[i].coefs[j]) get_coordinate(j);
		cerr << " = " << equations[i].coefs.back() << "\n";
	}
}

int gauss_elimination() {
	int nequas = equations.size();
//	assert(nequas > nvars); //can this happens?
	int cntSol = 0;
	vector<int> sol(nvars, -1);
	for (int col = 0, row = 0; row < nequas and col < nvars; col++) {
		int pivot = row;
		for (int j = row; j < nequas; j++) 
			if (equations[j].coefs[col] > equations[pivot].coefs[col]) pivot = j;
		if (equations[pivot].coefs[col] == 0) continue;
		++cntSol;
		sol[col] = row;
//		get_coordinate(col);
//		cerr << " is fixed\n";
		swap(equations[pivot], equations[row]);
		for (int j = 0; j < nequas; j++) if (j != row)
			if (equations[j].coefs[col] > 0) {
				equations[j] -= equations[row];
//				cerr << "equation " << j << " minused by equation " << row << "\n";
			} 
//		cerr << "phase " << row << ", pivot = " << pivot << "\n";
//		show_SLAE();
		++row;
	}
	for (int i = 0; i < nvars; i++) 
		if (sol[i] != -1) sol[i] = equations[sol[i]].coefs.back();
		else sol[i] = 0;
	//recheck
	for (int i = 0; i < nequas; i++) {
		int left_clause = 0;
		for (int j = 0; j < nvars; j++) 
			(left_clause += sol[j] * equations[i].coefs[j]) %= base;
		if (left_clause != equations[i].coefs.back()) return 0;
	}
	return cntSol;
//	if ()
	
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int x_dir[4] = { 0, 0,-1,+1};
	int y_dir[4] = {-1,+1, 0, 0};
	cin >> nrows >> ncols;
	nvars = nrows * ncols;
	for (int i = 1; i <= nrows; i++) {
		for (int j = 1; j <= ncols; j++) {
			cin >> board[i][j];
			if (board[i][j] == -1) continue;
			TEquation equa;
			equa.coefs.back() = board[i][j];
			for (int t = 0; t < 4; t++) {
				int x = i + x_dir[t], y = j + y_dir[t];
				if (x < 1 or x > nrows or y < 1 or y > ncols) continue;
				equa.coefs[get_index(x, y)] = 1;
			}
			equations.push_back(equa);
		}
	}
//	show_SLAE();
	int result = gauss_elimination();
	if (!result) return cout << 0, 0;
	result = nvars - result;
	string answer = "1";
	for (; result --> 0; ) {
		int rem = 0;
		for (int i = answer.size() - 1; i >= 0; i--) {
			int digit = 2 * (answer[i] - '0') + rem;
			answer[i] = (char) digit % 10 + '0';
			rem = digit / 10;
		}
		if (rem) answer = "1" + answer;
	}
	cout << answer;
}
