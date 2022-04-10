string S;
const int T = 1e6+N;
const int LG = 21;
pair<int,int> val[T];
int sa[T], rnk[T]; //i-th lexic. is .., S[i,] has order
int lcp[T]; //lcp[1..n-1] values in range [0..n-1]: lcp between S[sa[i],] and S[sa[i+1],]
bool cmp(int i, int j) { return val[i] < val[j]; }
void build_suffix_array() {
//	S = "diduduadi";
//	cerr << "builing SA for " << S << '\n';
	const int n = S.size();
	S = "." + S; //1-based index
	/* prefix_doubling */
	for (int i = 1; i <= n; i++)
		val[i] = make_pair(S[i],i);
	sort(val+1, val+1+n);
	for (int i = 1; i <= n; i++) {
		sa[i] = val[i].second;
		rnk[val[i].second] = i;
		if (i > 1)
			rnk[val[i].second] = rnk[val[i-1].second] + (val[i-1].first < val[i].first);
	}
//	for (int i = 1; i <= n; i++)
//		cerr << sa[i] << ": " << S.substr(sa[i], n-sa[i]+1) << '\n';
	vector<int> ids(n);
	iota(ids.begin(), ids.end(), 1);
	for (int t = 1; t <= LG; t++) {
		for (int i = 1, j = (1<<(t-1))+1; i <= n; i++, j++) {
			val[i] = make_pair(rnk[i], (j <= n) ? rnk[j] : 0);
		}
		sort(ids.begin(), ids.end(), cmp); //should be O(n)
		for (int i = 1; i <= n; i++) {
			sa[i] = ids[i-1];
			rnk[ids[i-1]] = i;
			if (i > 1)
				rnk[ids[i-1]] = rnk[ids[i-2]] + cmp(ids[i-2], ids[i-1]);
		}
//		cerr << "ITER " << t << '\n';
// 		for (int i = 1; i <= n; i++)
// 			cerr << sa[i] << ": " << S.substr(sa[i], n-sa[i]+1) << '\n';
	}
	for (int i = 1; i <= n; i++) rnk[sa[i]] = i;
	/* kasai */
	//i = rnk[1]+1
	//lcp(1,i) = x.  s[1..n] < s[i..n] => s[2..n] < s[i+1..n]
	//lcp(2,i+1) = x-1
	//i+1 đứng sau 2, j kề 2 (j = rnk[2]+1) thì lcp(2,j) >= lcp(2,i+1) = x-1
	for (int cnt = 0, i = 1; i <= n; i++) {
		if (rnk[i] == n) { cnt = 0; continue; }
		int j = sa[rnk[i]+1];
		while (i+cnt <= n and j+cnt <= n and S[i+cnt] == S[j+cnt]) cnt++;
		lcp[rnk[i]] = cnt;
		if (cnt) --cnt;
	}
}
