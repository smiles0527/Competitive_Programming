#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    
    vector<int> cowVotes(N);
    vector<int> f(N+1, 0);
    
    for (int i = 0; i < N; i++){
        cin >> cowVotes[i];
        f[cowVotes[i]]++;
    }
    
    for (int q = 0; q < Q; q++){
        int i, x;
        cin >> i >> x;
        int old = cowVotes[i-1];
        if(old != x){
            cowVotes[i-1] = x;
            f[old]--;
            f[x]++;
        }
        
        vector<int> S;
        for (int c = 1; c <= N; c++){
            if(f[c] > 0)
                S.push_back(c);
        }
    
        if(S.size() < 2){
            cout << 0 << "\n";
            continue;
        }
        
        int F = 0;
        for (int c = 1; c <= N; c++){
            F = max(F, f[c]);
        }
        
        int ans = 0;
        for (size_t i = 0; i < S.size(); i++){
            for (size_t j = i+1; j < S.size(); j++){
                int c1 = S[i], c2 = S[j];            
                if(f[c1] == F || f[c2] == F || (f[c1] + f[c2] >= F))
                    ans = max(ans, c2 - c1);
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}