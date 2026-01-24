#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        long long n, k;
        cin >> n >> k;
        
        vector<vector<long long>> dp(33, vector<long long>(k + 1, 0));
        
        for (int d = 0; d <= 32; d++) {
            dp[d][1] = d;
        }

        bool found = false;
        int answer = -1;
        
        for (int d = 1; d <= 32; d++) {
            for (int e = 2; e <= k; e++) {
                dp[d][e] = dp[d-1][e-1] + dp[d-1][e] + 1;

                if (dp[d][e] > 2000000000) {
                    dp[d][e] = 2000000001;
                }
            }
            
            if (dp[d][k] >= n) {
                answer = d;
                found = true;
                break;
            }
        }
        
        if (found) {
            cout << answer << "\n";
        } else {
            cout << "Impossible\n";
        }
    }
    
    return 0;
}