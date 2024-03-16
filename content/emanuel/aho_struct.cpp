const int E = 26;

struct AC {
    int nodes;
    vector<vi> go;
    vi suf, term, super;

    AC(): nodes(0) {node();}

    int node() {
        go.emplace_back(E, 0);
        suf.emplace_back(0);
        term.emplace_back(0);
        super.emplace_back(0);

        return nodes++;
    }

    void insert(const string& s) {
        int pos = 0;

        for(int i = 0; i < (int) s.size(); i++) {
            int nxt = s[i]-'a';

            if(go[pos][nxt] == 0)
                go[pos][nxt] = node();

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

    void clear() {
        go.clear();
        suf.clear();
        term.clear();
        super.clear();

        nodes = 0;
        node();
    }
};

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
    AC aho;

    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        aho.insert(s);
    }

    aho.build(0);
	
	return 0;
}

