#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long Ax, Ay, Bx, By;
        cin >> n >> Ax >> Ay >> Bx >> By;
        
        vector<pair<long long, long long>> p(n);
        for (int i = 0; i < n; i++) cin >> p[i].first;
        for (int i = 0; i < n; i++) cin >> p[i].second;
        
        sort(p.begin(), p.end());
        
        map<long long, pair<long long, long long>> ranges;
        for (int i = 0; i < n; i++) {
            long long x = p[i].first, y = p[i].second;
            if (ranges.find(x) == ranges.end()) {
                ranges[x] = {y, y};
            } else {
                ranges[x].first = min(ranges[x].first, y);
                ranges[x].second = max(ranges[x].second, y);
            }
        }
        
        vector<tuple<long long, long long, long long>> seg;
        for (auto& [x, r] : ranges) {
            seg.push_back({x, r.first, r.second});
        }
        
        int m = seg.size();
        vector<array<long long, 2>> dp(m + 1, {(long long)1e18, (long long)1e18});
        
        auto [x0, lo0, hi0] = seg[0];
        long long dx = x0 - Ax;
        long long span = hi0 - lo0;
        dp[0][0] = dx + abs(Ay - hi0) + span;
        dp[0][1] = dx + abs(Ay - lo0) + span;
        
        for (int i = 1; i < m; i++) {
            auto [px, plo, phi] = seg[i - 1];
            auto [cx, clo, chi] = seg[i];
            long long dx = cx - px;
            long long span = chi - clo;
            
            dp[i][0] = min(dp[i - 1][0] + dx + abs(plo - chi) + span,
                          dp[i - 1][1] + dx + abs(phi - chi) + span);
            dp[i][1] = min(dp[i - 1][0] + dx + abs(plo - clo) + span,
                          dp[i - 1][1] + dx + abs(phi - clo) + span);
        }
        
        auto [lx, llo, lhi] = seg[m - 1];
        long long ans = min(dp[m - 1][0] + (Bx - lx) + abs(llo - By),
                           dp[m - 1][1] + (Bx - lx) + abs(lhi - By));
        
        cout << ans << "\n";
    }
}