#include<bits/stdc++.h>
using namespace std;

struct Hungarian{
	int n;
	long long INF = LLONG_MAX; // Para maximo INF = 0 y negar costos
	vector< vector<long long> > cs;
	vector<int> L, R;
	Hungarian(int n_, int m_) : 
		n(max(n_, m_)), cs(n, vector<long long>(n)), L(n), R(n){
			for(int i=0; i<n_; i++){
				for(int j=0; j<m_; j++){
					cs[i][j] = INF;
				}
			}
		}

	void set(int x, int y, long long cost){
		cs[x][y] = cost;
	}

	long long assign(){
		int mat = 0;
		vector<long long> ds(n), u(n), v(n);
		vector<int> dad(n), son(n);
		for(int i=0; i<n; i++){
			u[i] = *min_element(cs[i].begin(),cs[i].end());
		}
		for(int j=0; j<n; j++){
			v[j] = cs[0][j] - u[0];
			for(int i=1; i<n; i++){
				v[j] = min(v[j], cs[i][j] - u[i]);
			}
		}
		L = R = vector<int>(n, -1);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(R[j] == -1 and cs[i][j] - u[i] - v[j] == 0){
					L[i] = j;
					R[j] = i;
					mat++;
					break;
				}
			}
		}
		while(mat < n){
			int s = 0;
			int j = 0;
			int i;
			while(L[s] != -1) s++;
			fill(dad.begin(),dad.end(),-1);
			fill(son.begin(),son.end(),0);
			for(int k = 0; k < n; k++){
				ds[k] = cs[s][k] - u[s] - v[k];
			}
			while(true){
				j = -1;
				for(int k=0; k<n; k++){
					if(!son[k] and (j == -1 or ds[k] < ds[j])){
						j = k;
					}
				}
				son[j] = 1;
				i = R[j];
				if(i == -1) break;
				for(int k=0; k<n; k++){
					if(!son[k]){
						auto new_ds = ds[j] + cs[i][k] - u[i] - v[k];
						if(ds[k] > new_ds){
							ds[k] = new_ds;
							dad[k] = j;
						}
					}
				}
			}
			for(int k=0; k<n; k++){
				if(k != j and son[k]){
					auto w = ds[k] - ds[j];
					v[k] += w;
					u[R[k]] -= w;
				}
			}
			u[s] += ds[j];
			while(dad[j] >= 0){
				int d = dad[j];
				R[j] = R[d];
				L[R[j]] = j;
				j = d;
			}
			R[j] = s;
			L[s] = j;
			mat++;
		}
		long long ans = 0LL;
		for(int i=0; i<n; i++){
			if(L[i] == -1) continue;
			ans += cs[i][L[i]];
		}
		return ans;
	}

	void print(){
		for(int i=0; i<n; i++){
			printf("%d %d\n",i+1,L[i]+1);
		}
	}
};

int n;

int main(){
	scanf("%d",&n);
	Hungarian H(n,n);
	int x;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			scanf("%d",&x);
			H.set(i,j,x);
		}
	}
	printf("%lld\n",H.assign());
	H.print();
	return 0;
}
