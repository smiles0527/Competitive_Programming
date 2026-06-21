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
ll fact[21];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= 20; i++) fact[i] = fact[i-1] * i;

    int t; cin >> t;
    string out;

    while (t--) {
        int type, n; cin >> type >> n;
        if (type == 1) {
            ll k; cin >> k;
            k--;                              // 0-indexed rank
            vector<int> avail;
            for (int i = 1; i <= n; i++) avail.push_back(i);
            for (int i = 0; i < n; i++) {
                ll f = fact[n - 1 - i];
                int idx = (int)(k / f);
                k %= f;
                out += to_string(avail[idx]);
                out += (i == n - 1 ? '\n' : ' ');
                avail.erase(avail.begin() + idx);
            }
        } else {
            vector<int> p(n);
            for (int i = 0; i < n; i++) cin >> p[i];
            vector<int> avail;
            for (int i = 1; i <= n; i++) avail.push_back(i);
            ll k = 0;
            for (int i = 0; i < n; i++) {
                int idx = (int)(lower_bound(avail.begin(), avail.end(), p[i]) - avail.begin());
                k += (ll)idx * fact[n - 1 - i];
                avail.erase(avail.begin() + idx);
            }
            out += to_string(k + 1);          // back to 1-indexed
            out += '\n';
        }
    }
    cout << out;
    return 0;
}