#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    static const long long MOD = 1e9 + 9;

    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);

    int N, M, K; cin >> N >> M >> K;

    vector<int> A(N+1), B(M+1);
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int j = 1; j <= M; j++) cin >> B[j];

    sort(A.begin()+1, A.end());
    sort(B.begin()+1, B.end());

    vector<vector<long long>> prev(N+1, vector<long long>(M+1, 1));
    vector<vector<long long>> cur(N+1, vector<long long>(M+1, 0));

    for(int k = 1; k <= K; k++){
        for(int i = 0; i <= N; i++) fill(cur[i].begin(), cur[i].end(), 0);

        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= M; j++){
                long long val = cur[i-1][j] + cur[i][j-1] - cur[i-1][j-1];
                val %= MOD;
                if(val < 0) val += MOD;
                if(A[i] > B[j]){
                    val += prev[i-1][j-1];
                    val %= MOD;
                }
                cur[i][j] = val;
            }
        }   
        swap(prev, cur);
    }

    cout << (prev[N][M] + MOD) % MOD << "\n";
    return 0;
}
