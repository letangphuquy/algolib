#include<bits/stdc++.h>
using namespace std; 
//Reference : cp-algorithms.com
const double PI = acos(-1);
using cd = complex<double>;

void fft(vector<cd>& a, bool invert) {
	//reversial-bit sorting
	const int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n>>1;
		for (;j&bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i > j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len *= 2) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		cd wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			cd w(1);
			for (int j = 0; j < len/2; j++, w *= wlen) {
				cd u = a[i+j], v = w * a[i+j+len/2];
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
			}
		}
	}
	if (invert)
		for (cd& y : a) y /= n;
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	int n = 1;
	while (n < (int) a.size() + b.size()) n <<= 1;
	//dft(A.B) = dft(A) dft(B) --> A.B = inverse(dft(A) . dft(B))
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	fa.resize(n); fb.resize(n);
	fft(a, false);
	fft(b, false);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(a, true);
	vector<int> res(n);
	for (int i = 0; i < n; i++) res[i] = round(fa[i].real());
	return res;
}

int main() 
{
}
