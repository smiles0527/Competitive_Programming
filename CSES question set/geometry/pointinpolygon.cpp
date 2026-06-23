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
inline int sgn(ll x) { return (x > 0) - (x < 0); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<ll> X(n), Y(n);
    for (int i = 0; i < n; i++) cin >> X[i] >> Y[i];

    string out;
    out.reserve(1 << 16);

    while (m--) {
        ll px, py; cin >> px >> py;
        bool boundary = false, inside = false;

        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            ll ax = X[i], ay = Y[i], bx = X[j], by = Y[j];

            // boundary: collinear + within bbox
            ll cr = (bx - ax) * (py - ay) - (by - ay) * (px - ax);
            if (cr == 0 &&
                min(ax, bx) <= px && px <= max(ax, bx) &&
                min(ay, by) <= py && py <= max(ay, by)) {
                boundary = true; break;
            }

            // ray cast to +x, half-open on y
            if ((ay > py) != (by > py)) {
                // x-intersection compared via sign of cross, oriented by edge dy
                ll t = (bx - ax) * (py - ay) - (px - ax) * (by - ay);
                int s = sgn(t) * sgn(by - ay);   // s>0 => intersection x > px
                if (s > 0) inside = !inside;
            }
        }

        out += boundary ? "BOUNDARY" : inside ? "INSIDE" : "OUTSIDE";
        out += '\n';
    }
    cout << out;
    return 0;
}