#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const ll INF = 4e18;

int n, K;
vi S0, S1;
vector<int> med;                                // med[l*(n+1)+r] = weighted median of [l,r]
vi prv, cur;

inline ll cost(int l, int r) {                  // min weighted distance, school at median
    int m = med[(size_t)l * (n + 1) + r];
    ll lc = S0[m] - S0[l - 1], lp = S1[m] - S1[l - 1];
    ll rc = S0[r] - S0[m],     rp = S1[r] - S1[m];
    return ((ll)m * lc - lp) + (rp - (ll)m * rc);
}

void solve(int lo, int hi, int ol, int oh) {    // D&C opt: cur[i]=min_j prv[j]+cost(j+1,i)
    if (lo > hi) return;
    int mid = (lo + hi) >> 1;
    ll best = INF; int bj = ol;
    int up = min(oh, mid - 1);
    for (int j = ol; j <= up; j++) {
        if (prv[j] >= INF) continue;
        ll v = prv[j] + cost(j + 1, mid);
        if (v < best) { best = v; bj = j; }
    }
    cur[mid] = best;
    solve(lo, mid - 1, ol, bj);
    solve(mid + 1, hi, bj, oh);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K;
    S0.assign(n + 1, 0); S1.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        ll c; cin >> c;
        S0[i] = S0[i - 1] + c;
        S1[i] = S1[i - 1] + c * i;
    }

    med.assign((size_t)(n + 1) * (n + 1), 0);
    for (int l = 1; l <= n; l++) {               // median pointer monotone in r
        int m = l;
        ll baseW = S0[l - 1];
        for (int r = l; r <= n; r++) {
            ll W = S0[r] - baseW;
            while ((S0[m] - baseW) * 2 < W) m++;
            med[(size_t)l * (n + 1) + r] = m;
        }
    }

    prv.assign(n + 1, INF); cur.assign(n + 1, INF);
    for (int i = 1; i <= n; i++) prv[i] = cost(1, i);   // k=1

    for (int k = 2; k <= K; k++) {
        fill(cur.begin(), cur.end(), INF);
        solve(k, n, k - 1, n - 1);               // i in [k,n], j in [k-1,i-1]
        swap(prv, cur);
    }

    cout << prv[n] << "\n";
}