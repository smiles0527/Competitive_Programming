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

const int LOG = 18, U = 1 << LOG;          // a_i <= n < 2^18
static ll F[U];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    for (int i = 0; i < n; i++) { int a; cin >> a; F[a]++; }   // frequency

    // superset-sum: F[m] = #{ a_i : a_i superset of m } = g(m)
    for (int b = 0; b < LOG; b++)
        for (int m = 0; m < U; m++)
            if (!(m & (1 << b))) F[m] += F[m | (1 << b)];

    vector<ll> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) pw[i] = pw[i-1] * 2 % MOD;

    for (int m = 0; m < U; m++) F[m] = (pw[F[m]] - 1 + MOD) % MOD;   // F(m) = 2^g(m) - 1

    // inverse superset-sum: recover exact(m) from F(m) = sum_{j superset m} exact(j)
    for (int b = 0; b < LOG; b++)
        for (int m = 0; m < U; m++)
            if (!(m & (1 << b))) F[m] = (F[m] - F[m | (1 << b)] % MOD + MOD) % MOD;

    string out; out.reserve(12 * (n + 1));
    for (int k = 0; k <= n; k++) { if (k) out += ' '; out += to_string(F[k]); }
    out += '\n';
    cout << out;
    return 0;
}