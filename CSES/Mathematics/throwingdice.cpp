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
const int K = 6;

struct Mat { ll a[K][K]; };

Mat mul(const Mat& A, const Mat& B) {
    Mat C;
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++) {
            ll s = 0;
            for (int k = 0; k < K; k++) s += A.a[i][k] * B.a[k][j] % MOD;
            C.a[i][j] = s % MOD;
        }
    return C;
}

Mat matpow(Mat base, ll e) {
    Mat r;
    for (int i = 0; i < K; i++) for (int j = 0; j < K; j++) r.a[i][j] = (i == j);
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

    ll n; cin >> n;

    // base cases f(0..5)
    ll f[6];
    f[0] = 1;
    for (int i = 1; i < 6; i++) {
        ll s = 0;
        for (int j = 1; j <= i; j++) s += f[i-j];
        f[i] = s % MOD;
    }
    if (n < 6) { cout << f[n] << '\n'; return 0; }

    // companion matrix: top row ones, subdiagonal identity
    Mat T;
    for (int i = 0; i < K; i++) for (int j = 0; j < K; j++) T.a[i][j] = 0;
    for (int j = 0; j < K; j++) T.a[0][j] = 1;
    for (int i = 1; i < K; i++) T.a[i][i-1] = 1;

    // advance from state (f5,f4,f3,f2,f1,f0) by T^(n-5)
    Mat P = matpow(T, n - 5);
    ll state[6] = { f[5], f[4], f[3], f[2], f[1], f[0] };
    ll res = 0;
    for (int j = 0; j < K; j++) res = (res + P.a[0][j] * state[j]) % MOD;

    cout << res << '\n';
    return 0;
}