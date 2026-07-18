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

void insert_line(int node, int l, int r, Line nw) {
    int mid = (l + r) >> 1;
    bool lef = nw.val(l) > tree[node].val(l);
    bool midb = nw.val(mid) > tree[node].val(mid);
    if (midb) swap(tree[node], nw);
    if (l == r) return;
    if (lef != midb) insert_line(node<<1, l, mid, nw);
    else insert_line(node<<1|1, mid+1, r, nw);
}

ll query(int node, int l, int r, int x) {
    ll res = tree[node].val(x);
    if (l == r) return res;
    int mid = (l + r) >> 1;
    if (x <= mid) return max(res, query(node<<1, l, mid, x));
    else return max(res, query(node<<1|1, mid+1, r, x));
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
            ll a, b; cin >> a >> b;
            insert_line(1, 0, X, Line{a, b});
        } else {
            int x; cin >> x;
            out += to_string(query(1, 0, X, x));
            out += '\n';
        }
    }
    cout << out;
    return 0;
}