#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<bool> have(n + 1, false);
        for (int& x : a) {
            cin >> x;
            have[x] = true;
        }
        
        vector<int> dp(n + 1, 1e9);
        
        for (int i = 1; i <= n; i++) {
            if (have[i]) dp[i] = 1;
            for (int d = 2; d * d <= i; d++) {
                if (i % d == 0) {
                    if (have[d] && dp[i / d] < 1e9)
                        dp[i] = min(dp[i], dp[i / d] + 1);
                    if (have[i / d] && dp[d] < 1e9)
                        dp[i] = min(dp[i], dp[d] + 1);
                }
            }
        }
        
        for (int i = 1; i <= n; i++)
            cout << (dp[i] >= 1e9 ? -1 : dp[i]) << " \n"[i == n];
    }
}