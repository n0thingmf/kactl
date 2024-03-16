vector<int> Centroid(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> centroid;
    vector<int> sz(n);

    function<void (int, int)> dfs = [&](int u, int prev) {
        sz[u] = 1;
        bool is_centroid = true;

        for(auto v : adj[u]) if(v != prev) {
            dfs(v, u);
            sz[u] += sz[v];
            if(sz[v] > n/2) is_centroid = false;
        }

        if(n-sz[u] > n/2) is_centroid = false;
        if(is_centroid) centroid.emplace_back(u);
    };
    dfs(0, -1);
    return centroid;
}

const int maxn = 1e5 + 10;
vector<int> adj[maxn];
int sz[maxn], pi[maxn];
bool block[maxn];
int n;

int centroid(int v, int p, int n) {
    sz[v] = 1;
    int mx=0, cen=0;
    for (auto u : adj[v]) if (u!=p && !block[u]) {
        cen ^= centroid(u, v, n);
        sz[v] += sz[u], mx=max(mx, sz[u]);
    }
    mx = max(mx, n-sz[v]);
    if (2*mx <= n) pi[cen=v]=p;
    return cen;
}

void decompose(int x, int p=-1, int m=n) {
    int cen = centroid(x, -1, m);
    if (~pi[cen]) sz[pi[cen]]=m-sz[cen];
    pi[cen]=p; block[cen]=1;
    for (auto v : adj[cen]) if (!block[v]) {
        decompose(v, cen, sz[v]);
    }
}
