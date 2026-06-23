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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    string out;
    while (t--) {
        int n; cin >> n;
        int x = 0;
        for (int i = 1; i <= n; i++) {
            int v; cin >> v;
            if (i % 2 == 0) x ^= v;     // even 1-based stairs = odd distance from floor
        }
        out += (x != 0 ? "first" : "second");
        out += '\n';
    }
    cout << out;
    return 0;
}