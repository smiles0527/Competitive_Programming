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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vii ed;
    ed.reserve(m);

    vector<vi> rg(n + 1);
    vi out(n + 1), ans;
    ans.reserve(n);

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        ed.pb({a, b});
    }

    for (ii e : ed) {
        out[e.f]++;
        rg[e.s].pb(e.f);
    }

    priority_queue<ll> pq;
    for (ll i = 1; i <= n; i++) {
        if (!out[i]) pq.push(i);
    }

    while (!pq.empty()) {
        ll v = pq.top();
        pq.pop();

        ans.pb(v);

        for (ll to : rg[v]) {
            out[to]--;
            if (!out[to]) pq.push(to);
        }
    }

    reverse(ans.begin(), ans.end());

    for (ll i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i + 1 == n];
    }

    return 0;
}