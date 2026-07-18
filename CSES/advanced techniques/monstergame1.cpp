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

    int n; ll x;
    cin >> n >> x;
    vi s(n + 1), fa(n + 1);
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> fa[i];

    auto bad = [](const Line &a, const Line &b, const Line &c) {     // b redundant on envelope
        return (long double)(c.b - a.b) * (a.k - b.k)
             <= (long double)(b.b - a.b) * (a.k - c.k);
    };

    vector<Line> hull;
    int head = 0;
    auto add = [&](Line ln) {                   // slopes non-increasing
        while ((int)hull.size() - head >= 2 &&
               bad(hull[hull.size() - 2], hull[hull.size() - 1], ln))
            hull.pop_back();
        hull.pb(ln);
    };
    auto query = [&](ll xq) {                    // queries non-decreasing
        while ((int)hull.size() - head >= 2 &&
               hull[head].eval(xq) >= hull[head + 1].eval(xq))
            head++;
        return hull[head].eval(xq);
    };

    add({x, 0});                                // implicit kill-0: pay s_i * x
    ll dp = 0;
    for (int i = 1; i <= n; i++) {
        dp = query(s[i]);                       // dp[i] = min_{j<i} dp[j] + s_i f_j
        add({fa[i], dp});                       // monster i as a future "previous kill"
    }

    cout << dp << "\n";
}