const int SUML = 500000 + 5;
const int E = 26;

int n;
int nodes = 1;
int suf[SUML];
int term[SUML];
int super[SUML];
int go[SUML][E];

void init() {
    nodes = 1;

    memset(term, 0, sizeof(term));
    memset(go, 0, sizeof(go));
    memset(suf, 0, sizeof(suf));
    memset(super, 0, sizeof(super));
}

void insert(const string& s) {
    int pos = 0;
    for(int i = 0; i < (int) s.size(); i++) {
        int nxt = s[i]-'a';
        if(go[pos][nxt] == 0) {
            go[pos][nxt] = nodes++;
        }
        pos = go[pos][nxt];
    }
    term[pos]++;
}

void build(int src=0) {
    queue<int> Q;
    Q.emplace(src);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();

        if(term[suf[u]]) super[u] = suf[u];
        else super[u] = super[suf[u]];

        for(int c = 0; c < E; c++) {
            if(go[u][c]) {
                int v = go[u][c];
                Q.emplace(v);

                suf[v] = u == 0 ? 0 : go[suf[u]][c];
            }
            else {
                go[u][c] = u == 0 ? 0 : go[suf[u]][c];
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    scanf("%d", &n);
    nodes = 1;
    for(int i = 1; i <= n; i++){
        string s; cin >> s;
        insert(s);
    }
    build(0);
	
    return 0;
}

