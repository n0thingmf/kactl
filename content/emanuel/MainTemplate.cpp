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
#define f first
#define s second 
#define bpc __builtin_popcountll//numero de bits para long long
#define bclz __builtin_clzll//leading zeros para ll 
#define max_bit(A) 31-__builtin_clz(A)

//cout << setprecision(12) << fixed;

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
long long random(long long l, long long r){
   return uniform_int_distribution<long long>(l,r)(rng);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
    int n = 20;

    vector<int>v[2];
    for(int i=0; i<2; i++) v[i].clear();

    v[0].pb(0);
    for(int i = 0; i < n; i++) v[1].pb(i);

    vector<int>parent(n, 0);

    while((int)v[1].size() > 0){

       vector<int>id;
       for(int i = 0; i < 2; i++){
          int idx = random(0, (int)v[i].size());
          id.pb(idx);
       }

       int val = v[1][id[1]];
       parent[val] = v[0][id[0]];
       v[1].erase(v[1].begin() + id[1]);
       v[0].pb(val);
    }

    cout << n << endl;

    for(int i = 0; i < n; i++)
       cout << parent[i] << " ";

    cout << endl;

    return 0;
}
