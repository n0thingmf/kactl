#include<bits/stdc++.h>
using namespace::std;

const int E = 26;
const int N = 90000 + 5;
const int SUML = 2 * N;

int n;
int q;
int L;
int last;
int nodes;
char s[N];
int p[SUML];
int head[N];
int len[SUML];
int link[SUML];
int nxt[SUML][E];
long long memo[SUML];

void sa_extend(int c){
	int cur = nodes++;
	len[cur] = len[last] + 1;
	int p = last;

	//firstpos[cur] = len(cur)-1;

	while(~p and !nxt[p][c]){
		nxt[p][c] = cur;
		p = link[p];
	}
	if(p == -1){
		link[cur] = 0;
	}
	else{
		int q = nxt[p][c];
		if(len[p] + 1 == len[q]){
			link[cur] = q;
		}
		else{
			int clone = nodes++;
			len[clone] = len[p] + 1;
			link[clone] = link[q];
			//firstpos[clone] = firstpos[q];
			memcpy(nxt[clone], nxt[q], sizeof(nxt[q]));
			while(~p and nxt[p][c] == q){
				nxt[p][c] = clone;
				p = link[p];
			}
			link[q] = link[cur] = clone;
		}
	}
	last = cur;
}

void build_automaton(){
	memset(link, -1, sizeof link);
	nodes++;
	for(int i = 0; s[i]; i++){
		int c = s[i] - 'a';
		sa_extend(c);
	}
}

void preprocess(){
	for(int i = 0; i < nodes; i++) head[len[i]]++;
	int sum = 0;
	for(int i = 0; i <= n; i++){
		sum += head[i];
		head[i] = sum - head[i];
	}
	for(int i = 0; i < nodes; i++) p[head[len[i]]++] = i;
	for(int i = nodes - 1; i >= 0; i--){
		int at = p[i];
		memo[at] = 0;
		for(int c = 0; c < E; c++){
			if(nxt[at][c]) memo[at] += memo[nxt[at][c]] + 1;
		}
	}
}

void dfs(int v) {
    vis[v] = 1;
    for(char c = 'a'; c <= 'z'; c++) {
        if(!st[v].next.count(c)) continue;
        int to = st[v].next[c];
 
        if(!vis[to]) dfs(to);
 
        tot[v] += tot[to];
    }
}

int main(){
	scanf("%s", s);
	n = strlen(s);
	build_automaton();
	preprocess();
	scanf("%d", &q);
	int k;
	while(q--){
		scanf("%d", &k);
		int pos = 0;
		while(k > 0){
			if(k == 0) break;
			for(int c = 0; c < E; c++){
				int v = nxt[pos][c];
				if(!v) continue;
				if(memo[v] + 1 >= k){
					putchar('a' + c);
					k--;
					pos = v;
					break;
				}
				k -= memo[v] + 1;
			}
		}
		putchar('\n');
	}

	// K-th substring

	for(int x : a) {
        if(x) cnt[st[x].link] += cnt[x];
        tot[x] = cnt[x];
    }
 
    dfs(0);
 
    //for(int i = 0; i < sz; i++)
        //cout << i << " " << tot[i] << "\n";
 
    ll k; cin >> k;
    k += s.size();
 
    if(k > tot[0]) {
        cout << "No such line.\n";
        return 0;
    }
 
    int p = 0;
 
    while(k > cnt[p]) {
        ll curr = cnt[p];
        for(char c = 'a'; c <= 'z'; c++) {
            if(!st[p].next.count(c)) continue;
 
            int to = st[p].next[c];
 
            if(curr + tot[to] >= k) {
                p = to;
                k -= curr;
                cout << c;
                break;
            }
 
            curr += tot[to];
        }
    }

	return 0;
}
