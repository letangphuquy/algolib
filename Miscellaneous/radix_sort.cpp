#include<bits/stdc++.h>
using namespace std;

typedef long long Int;

const int N = 1e7 + 50;
const int V = 1e6;

/*
Main idea
+ Instead of sorting digits by digits, I sort by 6 digits at once (base = 1e6)
+ DynamicArray to improve constant factor (faster than vectors)
+ differ than the one implemented quite long ago
+ manage elements by their id in original array
*/

struct DynamicArray {
	int size, head, *cont = nullptr;
	void reset(void) {
		head = size = 0;
		if (cont != nullptr) {
			delete cont;
			cont = nullptr;
		}
	}
	DynamicArray() { reset(); }
	int operator[] (int i) const { return cont[i]; }
	void operator++ (void) { ++size; }
	void resize(void) {
		head = 0;
		if (cont == nullptr)
			cont = new int[size];
	}
	void push_back(int v) {
		assert(head < size);
		cont[head++] = v;
	}
};

DynamicArray buckets[V];
int n;
Int a[N];
int b[N], c[N];

void radix_sort() 
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = a[i] / V;
		++buckets[c[i] = (a[i] % V)];
	}
	for (int v = 0; v < V; v++) buckets[v].resize();
	DynamicArray ids;
	for (int i = 1; i <= n; i++) {
		buckets[c[i]].push_back(i);
		++ids;
	}
	ids.resize();
	cerr << ids.size << '\n';
	// Three iterations - sort values up to 10^18 
	for (int turn = 0; turn < 3; turn++) {
		cerr << " TURN " << turn << '\n';
		ids.head = 0;
		for (int v = 0; v < V; v++) {
			for (int i = 0; i < buckets[v].size; i++)
				ids.push_back(buckets[v][i]);
			buckets[v].reset();
		}
		assert(ids.size == n);
		for (int i = 0; i < n; i++)
			++buckets[c[i] = (b[ids[i]] % V)];
		for (int v = 0; v < V; v++) buckets[v].resize();
		for (int i = 0, id; i < n; i++) {
			id = ids[i];
			buckets[c[i]].push_back(id);
			b[id] /= V;
		} 
	} 

	for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	radix_sort();
}
