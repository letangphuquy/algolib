
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
	int ids[T], cnt_le[T], ptr[T], ids2[T];
	for (int i = 1; i <= n; i++) ids[i] = i;
	for (int t = 0; t <= LG; t++) {
		if (t == 0) {
			for (int i = 1; i <= n; i++) val[i] = make_pair(S[i],0);
			sort(ids+1, ids+1+n, cmp);
		}
		else {
			for (int i = 1, j = (1<<(t-1))+1; i <= n; i++, j++)
				val[i] = make_pair(rnk[i], (j <= n) ? rnk[j] : 0);
			//sort by second
			int mx = 0;
			for (int i = 1; i <= n; i++) 
				maximize(mx, val[i].second),
				++cnt_le[val[i].second];
			for (int i = 0; i <= mx; i++) {
				ptr[i] = 1;
				if (i > 0) 
					ptr[i] += cnt_le[i-1],
					cnt_le[i] += cnt_le[i-1];			
			}
			for (int i = 1; i <= n; i++) {
				ids2[ptr[val[ids[i]].second]++] = ids[i];
			}
			for (int i = 0; i <= mx; i++) cnt_le[i] = 0;
			for (int i = 1; i <= n; i++) ids[i] = ids2[i];
			//sort by first
			mx = 0;
			for (int i = 1; i <= n; i++) 
				maximize(mx, val[i].first),
				++cnt_le[val[i].first];
			for (int i = 0; i <= mx; i++) {
				ptr[i] = 1;
				if (i > 0) 
					ptr[i] += cnt_le[i-1],
					cnt_le[i] += cnt_le[i-1];			
			}
			for (int i = 1; i <= n; i++) {
				ids2[ptr[val[ids[i]].first]++] = ids[i];
			}
			for (int i = 0; i <= mx; i++) cnt_le[i] = 0;
			for (int i = 1; i <= n; i++) ids[i] = ids2[i];
		}
		for (int i = 1; i <= n; i++) {
			sa[i] = ids[i];
			rnk[ids[i]] = i;
			if (i > 1)
				rnk[ids[i]] = rnk[ids[i-1]] + cmp(ids[i-1], ids[i]);
		}
//		cerr << "ITER " << t << '\n';
//		for (int i = 1; i <= n; i++)
//			cerr << sa[i] << ": " << S.substr(sa[i], n-sa[i]+1) << '\n';
		if (rnk[ids[n]] == n) break;
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
