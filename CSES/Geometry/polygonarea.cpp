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

    lll s = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        s += (lll)x[i] * y[j] - (lll)x[j] * y[i];
    }
    if (s < 0) s = -s;

    string out;
    if (s == 0) out = "0";
    else { while (s > 0) { out += char('0' + (int)(s % 10)); s /= 10; } reverse(out.begin(), out.end()); }
    cout << out << '\n';
    return 0;
}