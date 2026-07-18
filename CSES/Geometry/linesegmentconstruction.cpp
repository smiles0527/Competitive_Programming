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

inline int ori(ll ax, ll ay, ll bx, ll by, ll cx, ll cy) {
    return sgn((bx - ax) * (cy - ay) - (by - ay) * (cx - ax));
}

inline bool onseg(ll ax, ll ay, ll bx, ll by, ll px, ll py) {
    return min(ax, bx) <= px && px <= max(ax, bx) &&
           min(ay, by) <= py && py <= max(ay, by);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    string out;
    out.reserve(1 << 20);

    while (t--) {
        ll x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        int d1 = ori(x1, y1, x2, y2, x3, y3);
        int d2 = ori(x1, y1, x2, y2, x4, y4);
        int d3 = ori(x3, y3, x4, y4, x1, y1);
        int d4 = ori(x3, y3, x4, y4, x2, y2);

        bool hit = false;
        if (d1 * d2 < 0 && d3 * d4 < 0) hit = true;
        else if (d1 == 0 && onseg(x1, y1, x2, y2, x3, y3)) hit = true;
        else if (d2 == 0 && onseg(x1, y1, x2, y2, x4, y4)) hit = true;
        else if (d3 == 0 && onseg(x3, y3, x4, y4, x1, y1)) hit = true;
        else if (d4 == 0 && onseg(x3, y3, x4, y4, x2, y2)) hit = true;

        out += hit ? "YES" : "NO";
        out += '\n';
    }
    cout << out;
    return 0;
}