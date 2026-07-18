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
const ll MOD = 1e9+7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; string p;
    cin >> n >> p;
    int m = p.size();

    // KMP failure
    vector<int> fail(m, 0);
    for (int i = 1, k = 0; i < m; i++) {
        while (k && p[i] != p[k]) k = fail[k - 1];
        if (p[i] == p[k]) k++;
        fail[i] = k;
    }
    // automaton delta[q][c], q in [0,m]
    vector<array<int,26>> nxt(m + 1);
    for (int q = 0; q <= m; q++)
        for (int c = 0; c < 26; c++) {
            int k = q;
            while (k && p[k] - 'A' != c) k = fail[k - 1];
            if (k < m && p[k] - 'A' == c) k++;
            nxt[q][c] = k;
        }

    vector<ll> f(m, 0);
    f[0] = 1;
    for (int i = 0; i < n; i++) {
        vector<ll> g(m, 0);
        for (int q = 0; q < m; q++) {
            if (!f[q]) continue;
            for (int c = 0; c < 26; c++) {
                int t = nxt[q][c];
                if (t == m) continue;          // would complete pattern
                g[t] = (g[t] + f[q]) % MOD;
            }
        }
        f = move(g);
    }

    ll free = 0;
    for (int q = 0; q < m; q++) free = (free + f[q]) % MOD;

    ll tot = 1;
    for (int i = 0; i < n; i++) tot = tot * 26 % MOD;

    cout << (tot - free % MOD + MOD) % MOD << '\n';
    return 0;
}