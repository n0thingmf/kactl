bool substring_comparator(const pair<int, int>& a, const pair<int, int>& b) {
    int l1 = a.first, l2 = b.first;
    int r1 = a.first, r2 = b.first;
    int len1 = r1-l1+1, len2 = r2-l2+1;
    
    if(l1 == l2)
        return r1 < r2;

    // pos[i] : posición en el suffix array del sufijo que empieza por el índice 'i'
    int pl1 = pos[l1], pl2 = pos[l2];

    int curr_lcp = LCP(pl1, pl2); // STQuery(min(pl1, pl2), max(pl1, pl2)-1);

    if(curr_lcp >= max(len1, len2))
        return (len1 < len2) or (len1 == len2 and l1 < l2);

    if(len1 > curr_lcp and len2 > curr_lcp)
        return pl1 < pl2;

    return len1 < len2;
}

// Iterar por todos los substrings diferentes

void solve(const vi& a, const vi& lcp) {
	for(int i = 0; i <= n; i++) {
		int mx_lcp = max(lcp[i], lcp[i-1]);
		int unique_subs = n-a[i]-mx_lcp; 
	}

	vector<set<int> > banned(n+1);

	for(int i = 0; i <= n; i++) {
		if(lcp[i] == 0) continue;

		// lcp[i] : len(current substring)
		// a[i] : index substring

		int l = 0, r = i;

		while(l < r) {
			int m = (l+r+1) >> 1;

			if(LCP(m, i + 1) < lcp[i]) l = m;
			else r = m-1;
		}

		int L = l;

		if(banned[L+1].count(lcp[i])) continue;
		banned[L+1].insert(lcp[i]);

		l = i + 1, r = n;

		while(l < r) {
			int m = (l+r) >> 1;

			if(LCP(i, m) < lcp[i]) r = m;
			else l = m+1;
		}

		int R = l;

		int cnt = R-L-1; // number of current substring
		int repeated = max(LCP(L, i+1), LCP(i, R)); // subs[0, ..., max(lcp[L], lcp[R])]
	}
}

const int maxn = 1e5+5;
const int LOGN = 20;

int LCP_ST[maxn][LOGN];

void LCP_build(const vector<int>& lcp) {
    for(int i = 1; i <= (int) lcp.size(); i++) 
        LCP_ST[i][0] = lcp[i-1];

    for(int k = 1; (1 << k) <= (int) lcp.size(); k++) {
        int dis = 1 << (k-1);

        for(int i = 1; i + 2*dis -1 <= (int) lcp.size(); i++)
            LCP_ST[i][k] = min(LCP_ST[i][k-1], LCP_ST[i+dis][k-1]);
    }
}

int LCP(int L, int R) {
	if(L > R) swap(L, R);
    L++;

    int d = R-L+1;
    int k = 31- __builtin_clz(d);
    int dis = 1 << k;

    return min(LCP_ST[L][k], LCP_ST[R-dis+1][k]);
}

vector<int> lcp_array(vector<int> &s, vector<int> &a){
	int n = s.size();
	vector<int> rank(n);
	for(int i = 0; i < n; i++) rank[a[i]] = i;
	int k = 0;
	vector<int> lcp(n);
	for(int i = 0; i < n; i++){
		if(rank[i] + 1 == n){
			k = 0;
			continue;
		}
		int j = a[rank[i] + 1];
		while(i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
		lcp[rank[i]] = k;
		if(k) k--;
	}
	return lcp;
}

vector<int> suffix_array(vector<int> &s){
	int n = s.size();
	vector<int> a(n);
	vector<int> mp(n);
	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [&] (int i, int j){
		return s[i] < s[j];
	});
	mp[a[0]] = 0;
	for(int i = 1; i < n; i++){
		mp[a[i]] = mp[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
	}
	int len = 1;
	vector<int> head(n);
	vector<int> nmp(n);
	vector<int> sbs(n);
	while(len < n){
		for(int i = 0; i < n; i++) sbs[i] = (a[i] - len + n) % n;
		for(int i = n - 1; i >= 0; i--) head[mp[a[i]]] = i;
		for(int i = 0; i < n; i++){
			int x = sbs[i];
			a[head[mp[x]]++] = x;
		}
		nmp[a[0]] = 0;
		for(int i = 1; i < n; i++){
			if(mp[a[i - 1]] != mp[a[i]]){
				nmp[a[i]] = nmp[a[i - 1]] + 1;
			}
			else{
				int pre = mp[(a[i - 1] + len) % n];
				int cur = mp[(a[i] + len) % n];
				nmp[a[i]] = nmp[a[i - 1]] + (pre != cur);
			}
		}
		swap(mp, nmp);
		len <<= 1;
	}
	return a;
}

