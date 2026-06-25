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
char val[MX];
bool rev[MX];                                   // lazy reversal flag
int cnt = 0, root = 0;                           // node 0 = null sentinel

mt19937 rng(998244353);

int mk(char c) {
    int t = ++cnt;
    lc[t] = rc[t] = 0; sz[t] = 1; pr[t] = rng(); val[t] = c; rev[t] = false;
    return t;
}
inline void upd(int t) { if (t) sz[t] = sz[lc[t]] + sz[rc[t]] + 1; }
inline void push(int t) {                        // apply pending reversal to children
    if (t && rev[t]) {
        swap(lc[t], rc[t]);
        if (lc[t]) rev[lc[t]] ^= 1;
        if (rc[t]) rev[rc[t]] ^= 1;
        rev[t] = false;
    }
}

void split(int t, int k, int &a, int &b) {       // first k nodes -> a, rest -> b
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
    string str; cin >> str;
    for (int i = 0; i < n; i++) root = merge(root, mk(str[i]));

    while (m--) {
        int a, b; cin >> a >> b;
        int A, T, B, C;
        split(root, a - 1, A, T);                // A = [1,a-1]
        split(T, b - a + 1, B, C);               // B = [a,b], C = [b+1,end]
        rev[B] ^= 1;                             // lazily reverse B
        root = merge(merge(A, B), C);            // A + B + C
    }

    string out; out.reserve(n);
    vector<int> st;                              // iterative in-order with push-down
    int cur = root;
    while (cur || !st.empty()) {
        while (cur) { push(cur); st.pb(cur); cur = lc[cur]; }
        cur = st.back(); st.pop_back();
        out += val[cur];
        cur = rc[cur];
    }
    cout << out << "\n";
}