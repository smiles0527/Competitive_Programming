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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<pair<ll,ll>> p(n);
    for (auto& [x, y] : p) cin >> x >> y;
    sort(p.begin(), p.end());

    ll best = LLONG_MAX;
    set<pair<ll,ll>> act;   // ordered by (y, x)
    int left = 0;

    for (int i = 0; i < n; i++) {
        // integer ceil(sqrt(best)) for window radius
        ll d = (ll)ceil(sqrt((long double)best));
        // shrink window in x
        while (left < i && (p[i].first - p[left].first) * (p[i].first - p[left].first) > best) {
            act.erase({p[left].second, p[left].first});
            left++;
        }
        ll lo = p[i].second - d, hi = p[i].second + d;
        auto it1 = act.lower_bound({lo, LLONG_MIN});
        auto it2 = act.upper_bound({hi, LLONG_MAX});
        for (auto it = it1; it != it2; ++it) {
            ll dx = p[i].first - it->second;
            ll dy = p[i].second - it->first;
            ll dist = dx*dx + dy*dy;
            if (dist < best) best = dist;
        }
        act.insert({p[i].second, p[i].first});
    }

    cout << best << '\n';
    return 0;
}