#include <bits/stdc++.h>
using namespace std;
int main(){
    int T;cin >> T;
    while(T--){
        int N, K;cin >> N >> K;
        vector<int> S(N);
        for(int i=0;i<N;i++) cin >> S[i];
        const int INF = 1e9;
        vector<vector<int>> dp(N, vector<int>(N, INF));
        for(int i=0;i<N;i++) dp[i][i]=1;
        for(int len=2;len<=N;len++){
            for(int l=0;l+len-1<N;l++){
                int r=l+len-1;
                bool same = true;
                for(int i=l+1;i<=r;i++){
                    if(S[i]!=S[l]) {same = false; break;}
                }
                if(same) dp[l][r]=1;
                for(int m=l+1;m<=r;m++){
                    dp[l][r] = min(dp[l][r], dp[l][m-1] + dp[m][r]);
                }
                int L = r-l+1;
                for(int d=1; d<=L; d++){
                    if(L % d == 0){
                        int times = L / d;
                        if(times < 2) continue;
                        bool ok = true;
                        for(int t=1;t<times && ok;t++){
                            for(int i=0;i<d;i++){
                                if(S[l+i] != S[l+t*d+i]) {ok = false; break;}
                            }
                        }
                        if(ok) dp[l][r] = min(dp[l][r], dp[l][l+d-1]);
                    }
                }
            }
        }
        cout << (dp[0][N-1] <= K ? "YES" : "NO") << "\n";
    }
    return 0;
}
