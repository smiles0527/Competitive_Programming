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
ll josephus(ll n, ll k) {
    if (n == 1) return 1;
    ll half = n / 2;
    if (k <= half) return 2 * k;
    k -= half;
    ll m = n - half;
    ll sub = josephus(m, k);
    ll s;
    if (n & 1) s = ((sub - 2 + m) % m) + 1;   // odd: first removed is survivor-1, shift -1
    else       s = sub;                        // even: aligns with standard
    return 2 * s - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q; cin >> q;
    string out; out.reserve(1 << 21);
    while (q--) {
        ll n, k; cin >> n >> k;
        out += to_string(josephus(n, k));
        out += '\n';
    }
    cout << out;
    return 0;
}