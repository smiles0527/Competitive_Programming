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

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& v : a) cin >> v;

    int m = n - k;                         // levels to collapse
    int len = n;
    for (int t = 0; (1 << t) <= m; t++) {  // apply (1 + x^(2^t)) for each set bit of m
        if (!((m >> t) & 1)) continue;
        int sh = 1 << t;
        for (int j = 0; j + sh < len; j++) a[j] ^= a[j + sh];   // collapse 2^t levels at once
        len -= sh;
    }

    string out; out.reserve(11 * k);       // len == k here
    for (int j = 0; j < k; j++) { if (j) out += ' '; out += to_string(a[j]); }
    out += '\n';
    cout << out;
    return 0;
}