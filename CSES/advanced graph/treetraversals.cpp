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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    vi pre(n), in(n), pos(n + 1), ans;
    ans.reserve(n);

    for (ll &x : pre) cin >> x;
    for (ll i = 0; i < n; i++) {
        cin >> in[i];
        pos[in[i]] = i;
    }

    vector<array<ll, 5>> st;
    st.pb({0, 0, n - 1, 0, n - 1});

    while (!st.empty()) {
        auto cur = st.back();
        st.pop_back();

        ll tp = cur[0];

        if (tp == 1) {
            ans.pb(cur[1]);
            continue;
        }

        ll pl = cur[1], pr = cur[2], il = cur[3], ir = cur[4];
        if (pl > pr) continue;

        ll root = pre[pl];
        ll mid = pos[root];
        ll ls = mid - il;

        st.pb({1, root, 0, 0, 0});

        if (pl + ls + 1 <= pr) {
            st.pb({0, pl + ls + 1, pr, mid + 1, ir});
        }

        if (ls > 0) {
            st.pb({0, pl + 1, pl + ls, il, mid - 1});
        }
    }

    for (ll i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i + 1 == n];
    }

    return 0;
}