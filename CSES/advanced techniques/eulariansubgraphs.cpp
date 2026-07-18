#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int par[100005], sz[100005];

int find(int x) { while (par[x] != x) x = par[x] = par[par[x]]; return x; }
void uni(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a; sz[a] += sz[b];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { par[i] = i; sz[i] = 1; }

    for (int e = 0; e < m; e++) {
        int a, b; cin >> a >> b;
        uni(a, b);
    }

    int c = 0;
    for (int i = 1; i <= n; i++) if (find(i) == i) c++;

    ll pw = 1;                                  // 2^(m-n+c)
    int ex = m - n + c;
    for (int i = 0; i < ex; i++) pw = pw * 2 % MOD;

    cout << pw << "\n";
}