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
const ll MOD = 1e9 + 7;

ll power(ll a, ll b) {
    a %= MOD; if (a < 0) a += MOD;
    ll r = 1;
    while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; }
    return r;
}
ll inv(ll a) { return power(a, MOD - 2); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<vector<ll>> A(n, vector<ll>(m + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++) cin >> A[i][j];

    vector<int> where(m, -1);    // pivot column -> row
    int row = 0;
    for (int col = 0; col < m && row < n; col++) {
        // find pivot
        int sel = -1;
        for (int i = row; i < n; i++) if (A[i][col] != 0) { sel = i; break; }
        if (sel == -1) continue;
        swap(A[sel], A[row]);
        // normalize pivot row
        ll iv = inv(A[row][col]);
        for (int j = col; j <= m; j++) A[row][j] = A[row][j] * iv % MOD;
        // eliminate from all other rows
        for (int i = 0; i < n; i++) {
            if (i == row || A[i][col] == 0) continue;
            ll f = A[i][col];
            for (int j = col; j <= m; j++)
                A[i][j] = (A[i][j] - f * A[row][j] % MOD + MOD) % MOD;
        }
        where[col] = row;
        row++;
    }

    // build solution (free vars = 0)
    vector<ll> x(m, 0);
    for (int col = 0; col < m; col++)
        if (where[col] != -1) x[col] = A[where[col]][m];

    // consistency check
    for (int i = 0; i < n; i++) {
        ll s = 0;
        for (int j = 0; j < m; j++) s = (s + A[i][j] * x[j]) % MOD;
        // after RREF this reduces to checking zero rows, but verify directly
    }
    // detect 0 = nonzero rows
    for (int i = 0; i < n; i++) {
        bool allzero = true;
        for (int j = 0; j < m; j++) if (A[i][j] != 0) { allzero = false; break; }
        if (allzero && A[i][m] != 0) { cout << -1 << '\n'; return 0; }
    }

    string out;
    for (int j = 0; j < m; j++) { out += to_string(x[j]); out += (j == m-1 ? '\n' : ' '); }
    cout << out;
    return 0;
}