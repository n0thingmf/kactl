const int maxn = 1000;
int bit[maxn][maxn];

void update(int x, int y, int val) {
    for(; x < maxn; x += x & -x)
        for(int j = y; j < maxn; j += j & -j)
            bit[x][j] += val;
}

int get(int x, int y) {
    int ans = 0;

    for(; x; x -= x & -x)
        for(int j = y; j; j -= j & -j)
            ans += bit[x][j];

    return ans;
}

int get(int x1, int y1, int x2, int y2) {
    return get(x2, y2) - get(x1-1, y2) - get(x2, y1-1) + get(x1-1, y1-1);
}
