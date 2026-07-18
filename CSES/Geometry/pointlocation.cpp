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
    out.reserve(1 << 20);

    while (t--) {
        ll x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        ll cr = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
        out += (cr > 0 ? "LEFT" : cr < 0 ? "RIGHT" : "TOUCH");
        out += '\n';
    }
    cout << out;
    return 0;
}