#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
typedef long double Real;

const int MOD = 2004010501; //MOD > 2e9
const int base = 257;

const int MAX = 1e6 + 100;

const int NUM_MODS = 1;
const int MODS[4] = {MOD, 998244353, (int) 1e9 + 7, (int) 1e9 + 9};

int pwr[NUM_MODS][MAX];
bool IS_COMPUTED = false;
void init() {
	IS_COMPUTED = true;
	for (int t = 0; t < NUM_MODS; t++) {
		pwr[t][0] = 1;
		for (int i = 1; i < MAX; i++) pwr[t][i] = ((Int) pwr[t][i-1] * base) % MODS[t];
	}
}

struct Value {
	int d[NUM_MODS];
	Value() {}
	bool operator< (const Value& rhs) const {
		for (int t = 0; t < NUM_MODS; t++) 
			if (d[t] != rhs.d[t]) return d[t] < rhs.d[t];
		return false;
	}
	bool operator== (const Value& rhs) const {
		for (int t = 0; t < NUM_MODS; t++) if (d[t] != rhs.d[t]) return false;
		return true;
	}
};

const int SIDE = 1234; 
struct Hash2D {
	int val[NUM_MODS][SIDE][SIDE];
	int num_rows, num_cols;
	Hash2D() {}
	void build(const vector<string>& s) {
		if (!IS_COMPUTED) init();
		num_rows = s.size();
		num_cols = s[0].size();
		for (int t = 0; t < NUM_MODS; t++) {
			for (int id=1, r = 1; r <= num_rows; r++)
				for (int c = 1; c <= num_cols; c++) 
					val[t][r][c] = ((Int) s[r-1][c-1] * pwr[t][id++] + val[t][r-1][c] + val[t][r][c-1] - val[t][r-1][c-1]) % MODS[t];
		}
	}
	Value get_hash(const int& x, const int& y, const int& u, const int& v) const {
		Value res;
		for (int t = 0; t < NUM_MODS; t++) {
			int shift = pwr[t][(num_rows - u) * num_cols + (num_cols - v)];
			res.d[t] = ((Int) val[t][u][v] - val[t][x-1][v] - val[t][u][y-1] + val[t][x-1][y-1]) % MODS[t];
			res.d[t] = ((Int) res.d[t] * shift) % MODS[t];
			if (res.d[t] < 0) res.d[t] += MODS[t];
		}
		return res;
	}
} hash_board;
vector<string> board;
