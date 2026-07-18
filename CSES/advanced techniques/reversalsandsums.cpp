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

const int MX = 200005;
int lc[MX], rc[MX], sz[MX];
unsigned pr[MX];
ll val[MX], sm[MX];                              // value and subtree sum
bool rev[MX];
int cnt = 0, root = 0;

mt19937 rng(998244353);

int mk(ll c) {
    int t = ++cnt;
    lc[t] = rc[t] = 0; sz[t] = 1; pr[t] = rng(); val[t] = sm[t] = c; rev[t] = false;
    return t;
}
inline void upd(int t) {
    if (t) { sz[t] = sz[lc[t]] + sz[rc[t]] + 1; sm[t] = sm[lc[t]] + sm[rc[t]] + val[t]; }
}
inline void push(int t) {
    if (t && rev[t]) {
        swap(lc[t], rc[t]);
        if (lc[t]) rev[lc[t]] ^= 1;
        if (rc[t]) rev[rc[t]] ^= 1;
        rev[t] = false;
    }
}

void split(int t, int k, int &a, int &b) {
    if (!t) { a = b = 0; return; }
    push(t);
    if (sz[lc[t]] < k) {
        a = t;
        split(rc[t], k - sz[lc[t]] - 1, rc[t], b);
        upd(a);
    } else {
        b = t;
        split(lc[t], k, a, lc[t]);
        upd(b);
    }
}
int merge(int a, int b) {
    if (!a || !b) return a | b;
    push(a); push(b);
    if (pr[a] > pr[b]) { rc[a] = merge(rc[a], b); upd(a); return a; }
    else { lc[b] = merge(a, lc[b]); upd(b); return b; }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) { ll x; cin >> x; root = merge(root, mk(x)); }

    string out;
    while (m--) {
        int t, a, b; cin >> t >> a >> b;
        int A, B, C, T;
        split(root, a - 1, A, T);                // A = [1,a-1]
        split(T, b - a + 1, B, C);               // B = [a,b], C = [b+1,end]
        if (t == 1) rev[B] ^= 1;                 // reverse
        else { out += to_string(sm[B]); out += '\n'; }   // sum query
        root = merge(merge(A, B), C);            // A + B + C
    }
    cout << out;
}