const int MAX = 1e5 + 500;

const int NUM_MODS = 4;
const int MODS[4] = {2004010501, 998244353, (int) 1e9 + 7, (int) 1e9 + 9};

int pwr[NUM_MODS][MAX];
void init() {
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

struct Hash {
	int val[NUM_MODS][MAX];
	Hash(string s) {
		int n = s.size();
		for (int t = 0; t < NUM_MODS; t++)
			for (int i = 1; i <= n; i++) val[t][i] = ((Int) val[t][i-1] * base + s[i-1]) % MODS[t];
	}
	Value get_hash(const int& l, const int& r) const {
		Value res;
		for (int t = 0; t < NUM_MODS; t++) {
			res.d[t] = ((Int)-val[t][l-1] * pwr[t][r-l+1] + val[t][r]) % MODS[t];
			if (res.d[t] < 0) res.d[t] += MODS[t];
		}
		return res;
	}
};
