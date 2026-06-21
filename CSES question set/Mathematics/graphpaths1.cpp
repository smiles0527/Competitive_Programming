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
int n, m, K;

struct Mat { vector<vector<ll>> a; Mat(): a(n, vector<ll>(n, 0)) {} };

Mat mul(const Mat& A, const Mat& B) {
    Mat C;
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) {
            if (!A.a[i][k]) continue;
            ll aik = A.a[i][k];
            for (int j = 0; j < n; j++)
                C.a[i][j] = (C.a[i][j] + aik * B.a[k][j]) % MOD;
        }
    return C;
}

Mat matpow(Mat base, ll e) {
    Mat r;
    for (int i = 0; i < n; i++) r.a[i][i] = 1;
    while (e) {
        if (e & 1) r = mul(r, base);
        base = mul(base, base);
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K;
    Mat A;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        A.a[a-1][b-1] = (A.a[a-1][b-1] + 1) % MOD;   // parallel edges accumulate
    }

    Mat R = matpow(A, K);
    cout << R.a[0][n-1] << '\n';
    return 0;
}