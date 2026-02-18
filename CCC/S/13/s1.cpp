#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    using namespace std;

    int n;
    cin >> n;

    vector<int> dp(n+1, INT_MAX);
    dp[0] = 0;

    for (int i = 0; i < n-1; i++){

        if (dp[i] == INT_MAX) continue;
        
        int cur = i+1;

        /*for (int a = 1; a*a <= cur; a++){
            if (cur % a == 0){
                int nexta = cur + a;
                int b = cur / a;
                if (nexta <= n){
                    if (dp[i] + b < dp[nexta-1]){
                        dp[nexta-1] = dp[i] + b;
                    }
                }

                int nextb = cur + b;
                if (nextb <=n){
                    if (dp[i] + a < dp[nextb-1]){
                        dp[nextb - 1] = dp[i] + a;
                    }
                }
            }

        }*/


        for (int i )
    }

    cout << dp[n-1] << endl;

}