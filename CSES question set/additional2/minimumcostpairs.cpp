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

    int n; cin >> n;
    vector<ll> x(n);
    for (auto& v : x) cin >> v;
    sort(x.begin(), x.end());

    int m = n - 1;                      // gap edges
    vector<int> L(m), R(m);
    vector<ll> val(m);
    vector<char> dead(m, 0);
    for (int i = 0; i < m; i++) { val[i] = x[i+1] - x[i]; L[i] = i - 1; R[i] = i + 1; }

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    for (int i = 0; i < m; i++) pq.push({val[i], i});

    int K = n / 2, done = 0;
    ll cum = 0;
    string out;
    while (done < K && !pq.empty()) {
        auto [w, i] = pq.top(); pq.pop();
        if (dead[i] || w != val[i]) continue;       // stale heap entry
        cum += val[i];
        out += to_string(cum);
        out += (done == K - 1 ? '\n' : ' ');
        done++;

        int l = L[i], r = R[i];
        if (l >= 0 && r < m) {                       // interior: swap-back merge
            val[i] = val[l] + val[r] - val[i];
            dead[l] = dead[r] = 1;
            int ll_ = L[l], rr_ = R[r];
            L[i] = ll_; R[i] = rr_;
            if (ll_ >= 0) R[ll_] = i;
            if (rr_ < m) L[rr_] = i;
            pq.push({val[i], i});
        } else {                                     // boundary: no swap-back
            dead[i] = 1;
            if (l >= 0) { dead[l] = 1; int ll_ = L[l]; if (ll_ >= 0) R[ll_] = r; if (r < m) L[r] = ll_; }
            else if (r < m) { dead[r] = 1; int rr_ = R[r]; if (rr_ < m) L[rr_] = l; if (l >= 0) R[l] = rr_; }
        }
    }
    cout << out;
    return 0;
}