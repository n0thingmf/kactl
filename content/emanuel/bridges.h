// Finding articulation points O(N + M)

int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> vis;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (vis[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                IS_CUTPOINT(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        IS_CUTPOINT(v);
}

void find_cutpoints() {
    timer = 0;
    vis.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!vis[i])
            dfs (i);
    }
}

// Finding bridges in O(N+M)

int n; // number of nodes
vector<vii> adj; // adjacency list of graph

vector<bool> vis;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    for (auto e : adj[v]) {
        int to = e.first, id = e.second;
        if (to == p) continue;
        if (vis[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                IS_BRIDGE(v, to);
        }
    }
}

void find_bridges() {
    timer = 0;
    vis.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!vis[i])
            dfs(i);
    }
}

// BUILD TREE

vi idv;
vector<vi> tree;

void assign_id(int v, int ind) {
    idv[v] = ind;
    for(auto e : adj[v]) {
        int to = e.first, id = e.second;
        if(idv[to] != -1 or isBridge[id]) continue;

        assign_id(to, ind);
    }
}

void build_tree() {
    idv.clear(); idv.resize(n, -1);
    
    int ind = 0;
    for(int i = 0; i < n; i++) {
        if(idv[i] == -1) {
            assign_id(i, ind);
            ind++;
        }
    }

    tree.clear(); tree.resize(ind);

    for(int i = 0; i < (int) tree.size(); i++) {
        for(auto e : edge[i]) {
            int to = e.first, id = e.sencond;
            if(isBridge[id] and (idv[i] != idv[to])) {
                tree[idv[i]].pb(idv[to]);
            }
        }
    }
}


// -----------
// BRIDGE TREE DIAMETER
// -----------


#include <bits/stdc++.h>
using namespace std;
#define all(c) (c).begin(), (c).end()
#define rall(A) A.rbegin(),A.rend()
#define pb push_back 
#define dbg(x) do {cerr << #x <<" = " << (x) << endl; } while (false)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
//cout << setprecision(12) << fixed;

struct Edge {
    int u, v, id;
};

int n, m;
vector<vii> adj;
vi tin, low, idv;
vector<bool> vis, isBridge;
int timer;
vector<Edge> edges;

void init() {
    adj.clear(); adj.resize(n);
    tin.clear(); tin.resize(n, -1);
    low.clear(); low.resize(n, -1);
    vis.clear(); vis.resize(n, false);
    idv.clear(); idv.resize(n, -1);
    isBridge.clear(); isBridge.resize(m, false);
    edges.clear();

    timer = 0;
}

void dfs(int v, int p = -1) {
    vis[v] = 1;
    tin[v] = low[v] = timer++;

    for(auto e : adj[v]) {
        int to = e.first, id = e.second;

        if(to == p) continue;

        if(vis[to]) {
            low[v] = min(low[v], tin[to]);
        }
        else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);

            if(low[to] > tin[v]) {
                isBridge[id] = 1;
            }
        }
    }
}

void assign_id(int v, int ind) {
    idv[v] = ind;

    for(auto e : adj[v]) {
        int to = e.first, id = e.second;

        if(isBridge[id]) continue;
        if(idv[to] == -1) assign_id(to, ind);
    }
}

vector<vi> tree;

void build_bridge_tree() {
    int ind = 0;
    for(int i = 0; i < n; i++) {
        if(idv[i] == -1) {
            assign_id(i, ind);
            ind++;
        }
    }

    tree.clear(); tree.resize(ind);

    for(int i = 0; i < m; i++) {
        if(isBridge[i]) {
            int u = edges[i].u, v = edges[i].v;

            tree[idv[u]].pb(idv[v]);
            tree[idv[v]].pb(idv[u]);
        }
    }
}

ii diameter(int v, int p = -1) {
    int h[3] = {-1, -1, -1};
    int diam = 0;

    for(int to : tree[v]) {
        if(to == p) continue;

        auto d = diameter(to, v);
        diam = max(diam, d.first);

        h[0] = d.second;
        sort(h, h+3);
    }

    diam = max(diam, h[2]+h[1]+2);

    return {diam, h[2]+1};
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t = 1;
    while(t--) {
        cin >> n >> m;

        init();

        for(int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            u--; v--;

            adj[u].pb({v, i});
            adj[v].pb({u, i});

            edges.pb({u, v, i});
        }

        dfs(0);
        build_bridge_tree();

        int diam = diameter(0).first;
        cout << diam << "\n";
    }
    
    return 0;
}
