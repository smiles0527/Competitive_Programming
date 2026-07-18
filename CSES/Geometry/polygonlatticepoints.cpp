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
typedef __int128 lll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    lll a2 = 0;          // 2 * signed area
    ll B = 0;            // boundary lattice points
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        a2 += (lll)x[i] * y[j] - (lll)x[j] * y[i];
        ll dx = llabs(x[j] - x[i]), dy = llabs(y[j] - y[i]);
        B += std::__gcd(dx, dy);
    }
    if (a2 < 0) a2 = -a2;

    lll I = (a2 - B + 2) / 2;   // Pick: I = (2A - B + 2)/2

    // print I and B
    string out;
    if (I == 0) out = "0";
    else { lll t = I; while (t > 0) { out += char('0' + (int)(t % 10)); t /= 10; } reverse(out.begin(), out.end()); }
    out += ' ';
    out += to_string(B);
    cout << out << '\n';
    return 0;
}