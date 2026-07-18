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
const int OFF = 1000001;       // shift y in [-1e6,1e6] -> [1, 2e6+1]
const int SZ = 2000003;
ll bit[SZ];

void upd(int i, int d) { for (; i < SZ; i += i & -i) bit[i] += d; }
ll qry(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    // events: (x, type, a, b) ; type 0=add horiz, 1=vertical query, 2=remove horiz
    struct Ev { int x, type, a, b; };
    vector<Ev> ev;
    ev.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (y1 == y2) {
            // horizontal: x from x1..x2 at height y1
            int xl = min(x1, x2), xr = max(x1, x2);
            ev.push_back({xl, 0, y1, 0});
            ev.push_back({xr, 2, y1, 0});
        } else {
            // vertical: at x1, y from y1..y2
            int yb = min(y1, y2), yt = max(y1, y2);
            ev.push_back({x1, 1, yb, yt});
        }
    }

    sort(ev.begin(), ev.end(), [](const Ev& a, const Ev& b){
        return a.x < b.x || (a.x == b.x && a.type < b.type);
    });

    ll ans = 0;
    for (auto& e : ev) {
        if (e.type == 0) upd(e.a + OFF, 1);
        else if (e.type == 2) upd(e.a + OFF, -1);
        else ans += qry(e.b + OFF) - qry(e.a + OFF - 1);
    }

    cout << ans << '\n';
    return 0;
}