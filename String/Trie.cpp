#include<bits/stdc++.h>
using namespace std;

const int ABC = 26;

struct Node {
	int cnt, leaf = 0;
	Node* childs[ABC];
	Node() { leaf = cnt = 0; for (int c = 0; c < ABC; c++) childs[c] = nullptr; }
};

struct Trie {
	Node* root = new Node;
	Trie() {}
	void insert(string s) {
		Node* pos = root;
		for (auto c : s) {
			auto& child = pos -> childs[c-'a'];
			if (child == nullptr) child = new Node;
			pos = child; pos -> cnt++;
		}
		pos -> leaf++;
	}
	void erase(string s) {
		Node* pos = root;
		for (auto c : s) {
			auto child = pos -> childs[c-'a'];
			if (child == nullptr) break;
			pos = child; pos -> cnt--;
		}
		pos -> leaf--;
	}
	int query(string s) {
		int res = 0;
		Node* pos = root;
		for (auto c : s) pos = pos -> childs[c-'a'];
		res += pos -> cnt;
		return res;
	}
	void dfs(Node* pos, string s) {
		for (int c = 0; c < ABC; c++) {
			Node* child = pos -> childs[c];
			if (child != nullptr)
				dfs(child, s + char('a'+c));
		}
		if (pos -> leaf > 0) cout << s << '\n';
	}
};

int main()
{
	vector<string> dict;
	dict.push_back("cow");
	dict.push_back("goat");
	dict.push_back("cat");
	dict.push_back("dragon");
	dict.push_back("dog");
	dict.push_back("fish");
	dict.push_back("serpent");
	dict.push_back("hydra");
	Trie solver;
	for (auto word : dict) solver.insert(word);
	solver.dfs(solver.root, "");
}

