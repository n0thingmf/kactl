// initial values

// timer, ncomps = 0
// val.assign(n, 0); comp.assign(n, -1);
// val -> 0
// cont -> -1

vector<vi> adj;

vi val, comp, z, cont;
int timer, ncomps, ind;
vi roots;
vector<vi> adj_scc;

void init(int n) {
    adj.clear(); adj.resize(n);
    timer = ncomps = ind = 0;

    val.clear(); val.assign(n, 0);
    comp.clear(); comp.assign(n, -1);

    z.clear();
    roots.clear(); roots.resize(n);
}

int tarjan(int j) {
    int low = val[j] = ++timer, x; z.pb(j);

    for(int to : adj[j]) {
        if(comp[to] < 0) {
            low = min(low, val[to] ?: tarjan(to));
        }
    }

    if(low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.pb(x);
        } while(x != j);

        // Procesar scc
        for(int v : cont) {
            roots[v] = ind;
        }
        ind++;

        cont.clear();
        ncomps++;
    }

    return val[j] = low;
}

void build_scc_dag(int n) {
    adj_scc.clear(); adj_scc.resize(ncomps);

    for(int i = 0; i < n; i++) {
        for(int to : adj[i]) if(roots[i] != roots[to]) {
            adj_scc[roots[i]].pb(roots[to]);
        }
    }
}
