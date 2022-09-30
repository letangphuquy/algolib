const int MAX = 1e5 + 500;

const int base = 257;
const int NUM_MODS = 4;
const int MODS[] = {2004010501, 998244353, (int) 1e9 + 7, (int) 1e9 + 9};

int pwr[NUM_MODS][MAX];
bool IS_COMPUTED = false;
void init() {
	IS_COMPUTED = true;
	for (int t = 0; t < NUM_MODS; t++) {
		pwr[t][0] = 1;
		for (int i = 1; i < MAX; i++) pwr[t][i] = ((Int) pwr[t][i-1] * base) % MODS[t];
	}
}

typedef array<int,NUM_MODS> HValue;

struct Hash {
	vector<HValue> val;
	Hash() {
		val.clear();
		val.push_back(HValue);
	}
	void add_char(char c) {
		val.push_back(val.back());
		for (int t = 0; t < NUM_MODS; t++)
			val.back()[t] = ((Int) val.back()[t] * base + c) % MODS[t];
	}
	Hash(string s) {
		if (!IS_COMPUTED) init();
		for (auto c : s) add_char(c);
	}
	HValue get_hash(const int& l, const int& r) const {
		HValue res;
		for (int t = 0; t < NUM_MODS; t++) {
			res[t] = ((Int)-val[l-1][t] * pwr[t][r-l+1] + val[r][t]) % MODS[t];
			if (res[t] < 0) res[t] += MODS[t];
		}
		return res;
	}
};
