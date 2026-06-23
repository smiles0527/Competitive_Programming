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
struct P { ll x, y; };

ll cross(const P& O, const P& A, const P& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<P> p(n);
    for (auto& pt : p) cin >> pt.x >> pt.y;
    sort(p.begin(), p.end(), [](const P& a, const P& b){
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    vector<P> h(2 * n);
    int k = 0;

    // lower hull
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(h[k-2], h[k-1], p[i]) < 0) k--;
        h[k++] = p[i];
    }
    // upper hull
    int lower = k + 1;
    for (int i = n - 2; i >= 0; i--) {
        while (k >= lower && cross(h[k-2], h[k-1], p[i]) < 0) k--;
        h[k++] = p[i];
    }
    k--;   // drop last (== first)

    // dedup consecutive equal (collinear boundary may repeat endpoints)
    vector<P> hull;
    for (int i = 0; i < k; i++) {
        if (hull.empty() || !(hull.back().x == h[i].x && hull.back().y == h[i].y))
            hull.push_back(h[i]);
    }
    // also check wrap-around duplicate
    if (hull.size() > 1 && hull.front().x == hull.back().x && hull.front().y == hull.back().y)
        hull.pop_back();

    string out = to_string(hull.size());
    out += '\n';
    for (auto& pt : hull) { out += to_string(pt.x); out += ' '; out += to_string(pt.y); out += '\n'; }
    cout << out;
    return 0;
}