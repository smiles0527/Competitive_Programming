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

struct Line { ll k, b; ll eval(ll x) { return k * x + b; } };   // y = k x + b

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vi P(n + 1, 0);
    for (int i = 1; i <= n; i++) { ll v; cin >> v; P[i] = P[i - 1] + v; }

    auto bad = [](const Line &a, const Line &b, const Line &c) {     // b redundant
        return (long double)(c.b - a.b) * (a.k - b.k)
             <= (long double)(b.b - a.b) * (a.k - c.k);
    };

    const ll INF = 4e18;
    vector<ll> prev(n + 1, INF), cur(n + 1, INF);
    prev[0] = 0;
    for (int i = 1; i <= n; i++) prev[i] = P[i] * P[i];   // k=1: one block [1..i]

    vector<Line> hull;
    for (int k = 2; k <= K; k++) {
        hull.clear();
        int head = 0;
        auto add = [&](Line ln) {               // slopes -2P_j inserted descending
            while ((int)hull.size() - head >= 2 &&
                   bad(hull[hull.size() - 2], hull[hull.size() - 1], ln))
                hull.pop_back();
            hull.pb(ln);
        };
        auto query = [&](ll xq) {                // queries P_i ascending
            while ((int)hull.size() - head >= 2 &&
                   hull[head].eval(xq) >= hull[head + 1].eval(xq))
                head++;
            return hull[head].eval(xq);
        };

        fill(cur.begin(), cur.end(), INF);
        // j must be >= k-1 (need k-1 parts before), and dp_{k-1}[j] finite
        for (int i = k; i <= n; i++) {
            int j = i - 1;                       // newly available split point for this i
            if (prev[j] < INF) add({-2 * P[j], prev[j] + P[j] * P[j]});
            cur[i] = query(P[i]) + P[i] * P[i];  // dp_k[i] = min_j prev[j] + (P_i-P_j)^2
        }
        swap(prev, cur);
    }

    cout << prev[n] << "\n";
}