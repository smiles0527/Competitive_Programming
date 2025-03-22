#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, Q;
    cin >> N >> Q;
    vector<int> votes(N+1), freq(N+1, 0);
    for (int i = 1; i <= N; i++){
        cin >> votes[i];
        freq[votes[i]]++;
    }
    
    while(Q--){
        int pos, x;
        cin >> pos >> x;
        int old = votes[pos];
        if(old != x){
            votes[pos] = x;
            freq[old]--;
            freq[x]++;
        }
        
        int L = -1, R = -1;
        for (int cand = 1; cand <= N; cand++){
            if(freq[cand] > 0){
                L = cand;
                break;
            }
        }
        for (int cand = N; cand >= 1; cand--){
            if(freq[cand] > 0){
                R = cand;
                break;
            }
        }
        
        if(L == -1 || L == R){
            cout << 0 << "\n";
            continue;
        }
 
        int M = 0;
        for (int cand = 1; cand <= N; cand++){
            M = max(M, freq[cand]);
        }
        int min_M = -1, max_M = -1;
        for (int cand = 1; cand <= N; cand++){
            if(freq[cand] == M){
                if(min_M == -1)
                    min_M = cand;
                max_M = cand;
            }
        }
 
        int ans = 0;        
        if(freq[L] + freq[R] >= M)
            ans = R - L;
        else
            ans = max(max_M - L, R - min_M);
 
        cout << ans << "\n";
    }
    return 0;
}
