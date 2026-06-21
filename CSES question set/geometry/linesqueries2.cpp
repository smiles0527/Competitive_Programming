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
const ll NEG = LLONG_MIN / 4;
const int X = 100000;
struct Line { ll k, b; ll val(ll x) const { return k * x + b; } };
vector<Line> tree;

void li_insert(int node, int l, int r, Line nw) {
    int mid = (l + r) >> 1;
    bool lef = nw.val(l) > tree[node].val(l);
    bool midb = nw.val(mid) > tree[node].val(mid);
    if (midb) swap(tree[node], nw);
    if (l == r) return;
    if (lef != midb) li_insert(node<<1, l, mid, nw);
    else li_insert(node<<1|1, mid+1, r, nw);
}

void range_insert(int node, int l, int r, int ql, int qr, Line nw) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) { li_insert(node, l, r, nw); return; }
    int mid = (l + r) >> 1;
    range_insert(node<<1, l, mid, ql, qr, nw);
    range_insert(node<<1|1, mid+1, r, ql, qr, nw);
}

ll query(int node, int l, int r, int x) {
    ll res = tree[node].val(x);
    if (l == r) return res;
    int mid = (l + r) >> 1;
    if (x <= mid) res = max(res, query(node<<1, l, mid, x));
    else res = max(res, query(node<<1|1, mid+1, r, x));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    tree.assign(4 * (X + 1), Line{0, NEG});

    string out;
    out.reserve(1 << 21);

    while (n--) {
        int type; cin >> type;
        if (type == 1) {
            ll a, b; int l, r; cin >> a >> b >> l >> r;
            range_insert(1, 0, X, l, r, Line{a, b});
        } else {
            int x; cin >> x;
            ll q = query(1, 0, X, x);
            out += (q <= NEG / 2 ? string("NO") : to_string(q));
            out += '\n';
        }
    }
    cout << out;
    return 0;
}