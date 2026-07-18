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

const ll INF = 4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;

    vi shop(k);
    for (ll &x : shop) cin >> x;

    vector<vi> g(n + 1);
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    vector<array<ii, 2>> best(n + 1);
    for (ll i = 1; i <= n; i++) {
        best[i][0] = {INF, -1};
        best[i][1] = {INF, -1};
    }

    queue<pair<ii, ll>> q;

    auto add = [&](ll v, ll d, ll src) -> bool {
        if (best[v][0].s == src) {
            if (d >= best[v][0].f) return false;
            best[v][0].f = d;
            if (best[v][1].f < best[v][0].f) swap(best[v][0], best[v][1]);
            return true;
        }

        if (best[v][1].s == src) {
            if (d >= best[v][1].f) return false;
            best[v][1].f = d;
            if (best[v][1].f < best[v][0].f) swap(best[v][0], best[v][1]);
            return true;
        }

        if (d < best[v][0].f) {
            best[v][1] = best[v][0];
            best[v][0] = {d, src};
            return true;
        }

        if (d < best[v][1].f) {
            best[v][1] = {d, src};
            return true;
        }

        return false;
    };

    for (ll x : shop) {
        if (add(x, 0, x)) q.push({{x, 0}, x});
    }

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        ll v = cur.f.f;
        ll d = cur.f.s;
        ll src = cur.s;

        bool ok = false;
        if (best[v][0].s == src && best[v][0].f == d) ok = true;
        if (best[v][1].s == src && best[v][1].f == d) ok = true;
        if (!ok) continue;

        for (ll to : g[v]) {
            if (add(to, d + 1, src)) {
                q.push({{to, d + 1}, src});
            }
        }
    }

    for (ll i = 1; i <= n; i++) {
        ll ans = -1;

        if (best[i][0].s != i && best[i][0].f < INF) ans = best[i][0].f;
        else if (best[i][1].f < INF) ans = best[i][1].f;

        cout << ans << " \n"[i == n];
    }

    return 0;
}