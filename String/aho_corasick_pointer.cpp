
struct trie_node {
	trie_node *pi, *childs[26], *nxt[26];
	trie_node *parent; int edge;
	trie_node() {
		pi = parent = nullptr; edge = -1;
		for (int i = 0; i < 26; i++)
			childs[i] = nxt[i] = nullptr;
	}
};

struct aho_corasick {
	trie_node *root;
	aho_corasick() {
		root = new trie_node();
	}
	void insert(string s, int i) {
		trie_node *node = root;
		for (auto c : s) {
			auto& branch = node->childs[c-'a'];
			if (branch == nullptr) {
				branch = new trie_node();
				branch->parent = node;
				branch->edge = c-'a';
			}
			node = branch;
		}
		node->indices.push_back(i);
	}

	trie_node* pi(trie_node *node) {
		if (node->pi == nullptr) {
			node->pi = root;
			if (node->edge != -1 && node->parent != root)
				node->pi = next(pi(node->parent), node->edge);
		}
		return node->pi;
	}

	trie_node* next(trie_node *node, int i) {
		if (node->nxt[i] == nullptr) {
			node->nxt[i] = root;
			if (node->childs[i] == nullptr) {
				if (node->parent != root)
					node->nxt[i] = next(pi(node), i);
			}
			else
				node->nxt[i] = node->childs[i];
		}
		return node->nxt[i];
  }
};
