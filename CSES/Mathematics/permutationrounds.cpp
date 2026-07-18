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
const ll MOD = 1e9 + 7;
const int V = 200000;
int spf[V + 1];

ll power(ll a, ll b) {
    a %= MOD; ll r = 1;
    while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 2; i <= V; i++)
        if (!spf[i])
            for (int j = i; j <= V; j += i)
                if (!spf[j]) spf[j] = i;

    int n; cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    vector<char> vis(n + 1, 0);
    unordered_map<int,int> maxe;     // prime -> max exponent across cycle lengths

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        int len = 0, j = i;
        while (!vis[j]) { vis[j] = 1; j = p[j]; len++; }
        // factorize len, update max exponents
        int x = len;
        while (x > 1) {
            int q = spf[x], e = 0;
            while (x % q == 0) { x /= q; e++; }
            auto it = maxe.find(q);
            if (it == maxe.end() || it->second < e) maxe[q] = e;
        }
    }

    ll ans = 1;
    for (auto& [q, e] : maxe) ans = ans * power(q, e) % MOD;

    cout << ans << '\n';
    return 0;
}