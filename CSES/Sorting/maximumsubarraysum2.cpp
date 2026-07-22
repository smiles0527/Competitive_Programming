#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, a, b; cin >> n >> a >> b;
    vector<ll> p(n + 1);
    for (int i = 1; i <= n; i++) { cin >> p[i]; p[i] += p[i - 1]; }
    deque<int> q; ll ans = LLONG_MIN;
    for (int r = a; r <= n; r++) {
        while (!q.empty() && q.front() < r - b) q.pop_front();
        int l = r - a;
        while (!q.empty() && p[q.back()] >= p[l]) q.pop_back();
        q.push_back(l);
        ans = max(ans, p[r] - p[q.front()]);
    }
    cout << ans << '\n';
}
