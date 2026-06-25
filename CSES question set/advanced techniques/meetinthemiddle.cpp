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

void gen(vi &t, int l, int r, vi &out) {        // all subset sums of t[l..r)
    int m = r - l;
    out.resize((size_t)1 << m);
    out[0] = 0;
    for (int i = 0; i < m; i++) {
        ll v = t[l + i];
        int blk = 1 << i;
        for (int j = 0; j < blk; j++)
            out[blk + j] = out[j] + v;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll x;
    cin >> n >> x;
    vi t(n);
    for (auto &v : t) cin >> v;

    int h = n / 2;
    vi A, B;
    gen(t, 0, h, A);
    gen(t, h, n, B);

    sort(B.begin(), B.end());
    ll ans = 0;
    for (ll a : A) {
        ll need = x - a;
        auto pr = equal_range(B.begin(), B.end(), need);
        ans += pr.s - pr.f;
    }

    cout << ans << "\n";
}