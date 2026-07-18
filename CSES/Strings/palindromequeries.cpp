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
typedef unsigned long long ull;

const ll M1 = 1000000007, M2 = 998244353, B1 = 131, B2 = 137;
int n, m;
ll p1[200005], p2[200005];          // base powers
ll f1[200005], f2[200005], r1[200005], r2[200005];   // fenwicks

void upd(ll* t, int i, ll v, ll mod) { for (; i <= n; i += i & -i) t[i] = (t[i] + v) % mod; }
ll qr(ll* t, int i, ll mod) { ll s = 0; for (; i > 0; i -= i & -i) s = (s + t[i]) % mod; return s; }
ll rng(ll* t, int l, int r, ll mod) { return (qr(t, r, mod) - qr(t, l - 1, mod) + mod) % mod; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    string s; cin >> s;

    p1[0] = p2[0] = 1;
    for (int i = 1; i <= n; i++) { p1[i] = p1[i-1] * B1 % M1; p2[i] = p2[i-1] * B2 % M2; }

    // forward: position i (1-based) weight B^i ; reverse: position i weight B^(n+1-i)
    auto cval = [&](char c) { return (ll)(c - 'a' + 1); };
    vector<char> cur(n + 1);
    for (int i = 1; i <= n; i++) {
        cur[i] = s[i-1];
        ll v = cval(s[i-1]);
        upd(f1, i, v * p1[i] % M1, M1);
        upd(f2, i, v * p2[i] % M2, M2);
        upd(r1, i, v * p1[n + 1 - i] % M1, M1);
        upd(r2, i, v * p2[n + 1 - i] % M2, M2);
    }

    string out;
    out.reserve(1 << 21);
    while (m--) {
        int type; cin >> type;
        if (type == 1) {
            int k; char x; cin >> k >> x;
            ll old = cval(cur[k]), nw = cval(x);
            ll d = nw - old;
            upd(f1, k, ((d * p1[k]) % M1 + M1) % M1, M1);
            upd(f2, k, ((d * p2[k]) % M2 + M2) % M2, M2);
            upd(r1, k, ((d * p1[n + 1 - k]) % M1 + M1) % M1, M1);
            upd(r2, k, ((d * p2[n + 1 - k]) % M2 + M2) % M2, M2);
            cur[k] = x;
        } else {
            int a, b; cin >> a >> b;
            // palindrome <=> S_f * B^(n+1-a) == S_r * B^b , with S_r over the SAME range [a,b]
            // ll fwd1 = rng(f1, a, b, M1) * p1[n - a] % M1;     // shift so lowest exp aligns
            // ll fwd2 = rng(f2, a, b, M2) * p2[n - a] % M2;
            // int ra = n + 1 - b, rb = n + 1 - a;
            // ll rev1 = rng(r1, ra, rb, M1) * p1[n - ra] % M1;
            // ll rev2 = rng(r2, ra, rb, M2) * p2[n - ra] % M2;
            ll fwd1 = rng(f1, a, b, M1) * p1[n + 1 - a] % M1;
            ll fwd2 = rng(f2, a, b, M2) * p2[n + 1 - a] % M2;
            ll rev1 = rng(r1, a, b, M1) * p1[b] % M1;
            ll rev2 = rng(r2, a, b, M2) * p2[b] % M2;
            out += (fwd1 == rev1 && fwd2 == rev2) ? "YES" : "NO";
            out += '\n';
        }
    }
    cout << out;
    return 0;
}