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
const ll INF = (ll)4e18;
int n, m;
ll K;

struct Mat { vector<vector<ll>> a; Mat(): a(n, vector<ll>(n, INF)) {} };

Mat mul(const Mat& A, const Mat& B) {
    Mat C;
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) {
            if (A.a[i][k] == INF) continue;
            ll aik = A.a[i][k];
            for (int j = 0; j < n; j++) {
                if (B.a[k][j] == INF) continue;
                ll v = aik + B.a[k][j];
                if (v < C.a[i][j]) C.a[i][j] = v;
            }
        }
    return C;
}

Mat matpow(Mat base, ll e) {
    Mat r;
    for (int i = 0; i < n; i++) r.a[i][i] = 0;   // (min,+) identity
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
        int a, b; ll c; cin >> a >> b >> c;
        A.a[a-1][b-1] = min(A.a[a-1][b-1], c);   // keep lightest parallel edge
    }

    Mat R = matpow(A, K);
    ll ans = R.a[0][n-1];
    cout << (ans >= INF ? -1 : ans) << '\n';
    return 0;
}