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

    vi p(n - 2), deg(n + 1, 1);
    for (ll &x : p) {
        cin >> x;
        deg[x]++;
    }

    ll ptr = 1;
    while (deg[ptr] != 1) ptr++;

    ll leaf = ptr;

    vii ans;
    ans.reserve(n - 1);

    for (ll x : p) {
        // ll leaf = ptr;
        ans.pb({leaf, x});

        deg[leaf]--;
        deg[x]--;

        // if (deg[x] == 1 && x < ptr) {
        //     ptr = x;
        // } else {
        //     while (ptr <= n && deg[ptr] != 1) ptr++;
        // }

        if (deg[x] == 1 && x < ptr) {
            leaf = x;
        } else {
            while (ptr <= n && deg[ptr] != 1) ptr++;
            leaf = ptr;
        }
    }

    vi rem;
    for (ll i = 1; i <= n; i++) {
        if (deg[i] == 1) rem.pb(i);
    }

    ans.pb({rem[0], rem[1]});

    for (ii e : ans) {
        cout << e.f << ' ' << e.s << '\n';
    }

    return 0;
}