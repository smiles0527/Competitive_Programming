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

const int LOG = 20, U = 1 << LOG;          // x_i < 2^20
static int sub[U], sup[U];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) { cin >> x[i]; sub[x[i]]++; sup[x[i]]++; }

    // subset-sum: sub[m] = #{ y : y subset of m }
    for (int b = 0; b < LOG; b++)
        for (int m = 0; m < U; m++)
            if (m & (1 << b)) sub[m] += sub[m ^ (1 << b)];

    // superset-sum: sup[m] = #{ y : y superset of m }
    for (int b = 0; b < LOG; b++)
        for (int m = 0; m < U; m++)
            if (!(m & (1 << b))) sup[m] += sup[m | (1 << b)];

    int full = U - 1;
    string out; out.reserve(20 * n);
    for (int i = 0; i < n; i++) {
        int xi = x[i];
        int c1 = sub[xi];                  // y | x = x  <=>  y subset of x
        int c2 = sup[xi];                  // y & x = x  <=>  y superset of x
        int c3 = n - sub[xi ^ full];       // y & x != 0  <=>  not (y subset of ~x)
        out += to_string(c1); out += ' ';
        out += to_string(c2); out += ' ';
        out += to_string(c3); out += '\n';
    }
    cout << out;
    return 0;
}