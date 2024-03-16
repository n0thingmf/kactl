// complexity: O(NlogN)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int SUML = 1e5+5;
const int E = 26;
 
struct AC {
    int nodes;
    vector<vector<int>> go;
    vi suf, term, super;
    vector<long long> val;

    AC(): nodes(0) {node();}

    int node() {
        go.emplace_back(E, 0);
        suf.emplace_back(0);
        term.emplace_back(0);
        super.emplace_back(0);
        val.emplace_back(0);

        return nodes++;
    }

    void insert(const string& s, ll x) {
        int pos = 0;

        for(int i = 0; i < (int) s.size(); i++) {
            int nxt = s[i]-'a';

            if(go[pos][nxt] == 0)
                go[pos][nxt] = node();

            pos = go[pos][nxt];
        }

        term[pos]++;
        val[pos] += x;
    }

    void build(int src=0) {
        queue<int> Q;
        Q.emplace(src);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();

            if(term[suf[u]]) super[u] = suf[u];
            else super[u] = super[suf[u]];

            val[u] += val[suf[u]];

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

    ll process(const string& s) {
        int pos = 0;
        ll ans = 0;

        for(int i = 0; i < (int) s.size(); i++) {
            int nxt = s[i]-'a';
            pos = go[pos][nxt];

            ans += val[pos];
        }

        return ans;
    }

    void clear() {
        go.clear();
        suf.clear();
        term.clear();
        super.clear();
        val.clear();

        nodes = 0;
        node();
    }
};
 
const int LOGN = 20;

struct DAC {
    vector<pair<string, int> > sv[LOGN];
    AC aho[LOGN];

    void insert(const string& s, ll x) {
        int pos = 0;

        for(int i = 0; i < LOGN; i++) {
            if(sv[i].empty()) {
                pos = i;
                break;
            }
        }

        sv[pos].pb({s, x});
        aho[pos].insert(s, x);

        for(int i = 0; i < pos; i++) {
            for(const auto& p : sv[i]) {
                sv[pos].pb(p);
                aho[pos].insert(p.first, p.second);
            }
            sv[i].clear();
            aho[i].clear();
        }

        aho[pos].build();
    }

    ll process(const string& s) {
        ll ans = 0;

        for(int i = 0; i < LOGN; i++) 
            ans += aho[i].process(s);

        return ans;
    }
};
 
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
 
    DAC aho;
    int q; cin >> q;

    while(q--) {
        int tp; cin >> tp;

        if(tp == 1) {
            string s; cin >> s;
            ll x; cin >> x;

            aho.insert(s, x);
        }
        else {
            string t; cin >> t;

            cout << aho.process(t) << endl;
        }
    }
        
    return 0;
}
