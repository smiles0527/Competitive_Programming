#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int n;
vector<int> g[200005];
int da[200005], db[200005];

int bfs(int s, int *d) {
    for (int i = 1; i <= n; i++) d[i] = -1;
    d[s] = 0;
    int far = s;
    static int q[200005];
    int head = 0, tail = 0;
    q[tail++] = s;
    while (head < tail) {
        int u = q[head++];
        if (d[u] > d[far]) far = u;
        for (int v : g[u]) if (d[v] == -1) {
            d[v] = d[u] + 1;
            q[tail++] = v;
        }
    }
    return far;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; scanf("%d %d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int a = bfs(1, da);   // a = diameter endpoint
    int b = bfs(a, da);   // da now holds dist from a; b = other endpoint
    bfs(b, db);           // db holds dist from b

    for (int v = 1; v <= n; v++) {
        printf("%d", max(da[v], db[v]));
        putchar(v == n ? '\n' : ' ');
    }
    return 0;
}