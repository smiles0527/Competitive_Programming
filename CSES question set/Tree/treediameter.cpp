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
int dist_[200005];

int bfs(int s) {
    fill(dist_ + 1, dist_ + n + 1, -1);
    dist_[s] = 0;
    int far = s;
    int head = 0, tail = 0;
    static int q[200005];
    q[tail++] = s;
    while (head < tail) {
        int u = q[head++];
        if (dist_[u] > dist_[far]) far = u;
        for (int v : g[u]) if (dist_[v] == -1) {
            dist_[v] = dist_[u] + 1;
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
    int u = bfs(1);     // farthest from arbitrary root -> diameter endpoint
    bfs(u);
    printf("%d\n", dist_[bfs(u)]);
    return 0;
}