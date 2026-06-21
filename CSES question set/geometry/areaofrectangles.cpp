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
struct Edge { int x, yl, yr, type; };

int n;
vector<ll> ys;
vector<int> cnt;
vector<ll> cov;

int LEN;             // number of elementary intervals = ys.size()-1

void build(int node, int l, int r) {
    cnt[node] = 0; cov[node] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(node<<1, l, mid);
    build(node<<1|1, mid+1, r);
}

void pull(int node, int l, int r) {
    if (cnt[node] > 0) cov[node] = ys[r+1] - ys[l];
    else if (l == r) cov[node] = 0;
    else cov[node] = cov[node<<1] + cov[node<<1|1];
}

void update(int node, int l, int r, int ql, int qr, int v) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) { cnt[node] += v; pull(node, l, r); return; }
    int mid = (l + r) >> 1;
    update(node<<1, l, mid, ql, qr, v);
    update(node<<1|1, mid+1, r, ql, qr, v);
    pull(node, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<Edge> ev;
    ev.reserve(2 * n);
    ys.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        ev.push_back({x1, y1, y2, +1});
        ev.push_back({x2, y1, y2, -1});
        ys.push_back(y1); ys.push_back(y2);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    LEN = (int)ys.size() - 1;       // elementary intervals [ys[i], ys[i+1])

    sort(ev.begin(), ev.end(), [](const Edge& a, const Edge& b){ return a.x < b.x; });

    cnt.assign(4 * LEN, 0);
    cov.assign(4 * LEN, 0);
    build(1, 0, LEN - 1);

    ll area = 0, prevx = 0;
    for (int i = 0; i < (int)ev.size(); ) {
        int cx = ev[i].x;
        if (i > 0) area += cov[1] * (ll)(cx - prevx);
        while (i < (int)ev.size() && ev[i].x == cx) {
            int yl = (int)(lower_bound(ys.begin(), ys.end(), ev[i].yl) - ys.begin());
            int yr = (int)(lower_bound(ys.begin(), ys.end(), ev[i].yr) - ys.begin());
            // cover elementary intervals [yl, yr-1]
            update(1, 0, LEN - 1, yl, yr - 1, ev[i].type);
            i++;
        }
        prevx = cx;
    }

    cout << area << '\n';
    return 0;
}