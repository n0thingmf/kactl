
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 5;

vector<int> adj[maxn];
vector<int> t(4 * maxn, 0);

void update(int v, int tl, int tr, int pos, int delta, vector<int>& t) {
	if(tl == tr) {
		t[v] += delta;
	}
	else {
		int tm = (tl+tr) >> 1;
		if(pos <= tm) update(v * 2, tl, tm, pos, delta, t);
		else update(v * 2 + 1, tm+1, tr, pos, delta, t);

		t[v] = t[v * 2] + t[v * 2 + 1];
	}
}

pair<int, int> query(int v, int tl, int tr, int pos, vector<int>& t) {
	if(tl == tr) {
		return {tl, pos};
	}
	else {
		int tm = (tl+tr) >> 1;

		if(pos <= t[v * 2]) return query(v * 2, tl, tm, pos, t);
		else return query(v * 2 + 1, tm+1, tr, pos - t[v * 2], t);
	}
}

int get_cant(int v, int tl, int tr, int l, int r, vector<int>& t) {
	if(tr < l or r < tl) return 0;
	if(tl == l and tr == r) {
		return t[v];
	}
	else {
		int tm = (tl+tr) >> 1;
		return get_cant(v * 2, tl, tm, l, min(r, tm), t) + get_cant(v * 2 + 1, tm+1, tr, max(tm+1, l), r, t);
	}
}


int sz[maxn];

struct Query1 {
	int x, k, id;
};

struct Query2 {
	int x, num_son, ban, id;
};

vector<Query1> queries[maxn];
vector<Query2> queries2[maxn];
int n;

int pos_in_curr[maxn];
vector<int> curr;

int st[maxn];
int node[maxn];
int timer = 0;

void predfs(int v, int p=-1) {
	st[v] = timer++;
	node[st[v]] = v;

	sz[v] = 1;
	for(int to : adj[v]) if(to != p) {
		predfs(to, v);
		sz[v] += sz[to];
	}
}

ll ans[maxn];

void dfs(int v, int p=-1) {
	pos_in_curr[v] = curr.size();
	curr.push_back(v);

	update(1, 0, n-1, v, sz[v], t);
	if(p != -1) update(1, 0, n-1, p, -sz[v], t);

	for(int to : adj[v]) if(to != p) {
		dfs(to, v);
	}


	for(Query1& q : queries[v]) {
		auto pp = query(1, 0, n-1, q.k, t);

		int lca = pp.first;
		int num_son = pp.second;

		ans[q.id] += lca * 1ll * n;

		if(lca == v) {
			queries2[lca].push_back({lca, num_son, -1, q.id});
		}
		else {
			int ban = curr[pos_in_curr[lca] + 1];

			queries2[lca].push_back({lca, num_son, ban, q.id});
		}
	}

	update(1, 0, n-1, v, -sz[v], t);
	if(p != -1) update(1, 0, n-1, p, sz[v], t);

	pos_in_curr[v] = -1;
	curr.pop_back();
}

vector<pair<int, int>> all;
vector<pair<int, int>> banned_vertex[maxn];

vector<int> g(4 * maxn, 0);

void dfs2(int v, int p=-1, bool keep=0) {
	int big_child = -1, mx = 0;
	for(int to : adj[v]) if(to != p) {
		if(sz[to] > mx) {
			big_child = to;
			mx = sz[to];
		}
	}

	for(int to : adj[v]) if(to != p and to != big_child) {
		dfs2(to, v, 0);

		for(int i = st[to]; i < st[to] + sz[to]; i++) {
			int x = node[i];
			update(1, 0, n-1, x, 1, g);
		}
	}

	if(big_child != -1) {
		dfs2(big_child, v, 1);

	}

	for(auto& q : queries2[v]) {
		if(q.ban == -1) {
			all.push_back({q.num_son, q.id});
		}
		else {
			banned_vertex[q.ban].push_back({q.num_son, q.id});
		}
	}

	update(1, 0, n-1, v, 1, t);
	update(1, 0, n-1, v, 1, g);

	if(big_child != -1) {
		for(auto e : banned_vertex[big_child]) {

			ans[e.second] += query(1, 0, n-1, e.first, g).first;
		}
	}

	update(1, 0, n-1, v, -1, g);

	for(int to : adj[v]) if(to != p and to != big_child) {
		for(int i = st[to]; i < st[to] + sz[to]; i++) {
			int x = node[i];

			update(1, 0, n-1, x, -1, g);
			update(1, 0, n-1, x, 1, t);
		}
	}

	for(auto e : all) {
		ans[e.second] += query(1, 0, n-1, e.first, t).first;
	}

	for(int to : adj[v]) if(to != p and to != big_child) {
		if(banned_vertex[to].empty()) continue;
		for(int i = st[to]; i < st[to] + sz[to]; i++) {
			int x = node[i];
			update(1, 0, n-1, x, -1, t);
		}
		for(auto e : banned_vertex[to]) {
			ans[e.second] += query(1, 0, n-1, e.first, t).first;
		}
		for(int i = st[to]; i < st[to] + sz[to]; i++) {
			int x = node[i];
			update(1, 0, n-1, x, 1, t);
		}
	}

	if(!keep) {
		for(int i = st[v]; i < st[v] + sz[v]; i++) {
			int x = node[i];
			update(1, 0, n-1, x, -1, t);
		}
	}
	
	for(auto& q : queries2[v]) {
		if(q.ban == -1) {
			all.pop_back();
		}
		else {
			banned_vertex[q.ban].pop_back();
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	int q; cin >> q;
	int root = -1;
	for(int i = 0; i < n; i++) {
		int p; cin >> p;
		if(p == 0) {
			root = i;
			continue;
		}
		p--;
		adj[i].push_back(p);
		adj[p].push_back(i);
	}

	for(int i = 0; i < q; i++) {
		ll pos; cin >> pos;
		pos--;

		int x = pos / n;
		int k = pos % n;

		queries[x].push_back({x, k + 1, i});
		ans[i] = x * 1ll * n * n;
	}

	predfs(root);
	dfs(root);
	dfs2(root);

	for(int i = 0; i < q; i++) {
		cout << ans[i] << " ";
	}

	return 0;
}
