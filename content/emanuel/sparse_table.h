const int maxn = 1e5+5;
const int LOGN = 20;

int ST[maxn][LOGN];

int f(int a, int b) {return min(a,b);}

void STBuild(const vi& v) {
    for(int i = 1; i <= (int) v.size(); i++) 
        ST[i][0] = v[i]; // Cuidado con los índices. Si 'a' es 0-indexado, entonces: ST[i][0] = a[i-1];

    for(int k = 1; (1 << k) <= (int) v.size(); k++) {
        int dis = 1 << (k-1);

        for(int i = 1; i + 2*dis -1 <= (int) v.size(); i++)
            ST[i][k] = f(ST[i][k-1], ST[i+dis][k-1]);
    }
}

int STQuery(int L, int R) {
    // Cuidado con los índices: Las querys consideran que el array a consultar está 1-indexado.
    // Por lo que, si tu array es 0-indexado, y quieres consultar para [0, n-1] -> L = 1, R = n
    // Es decir, aumentamos en uno a L y R: L++; R++;

    int d = R-L+1;
    int k = 31- __builtin_clz(d);
    int dis = 1 << k;

    return f(ST[L][k], ST[R-dis+1][k]);
}

