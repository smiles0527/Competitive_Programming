#include <iostream>
#include <vector>
#include <set>
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
     
    set<int> S;
    for (int c = 1; c <= N; c++){
        if(f[c] > 0)
            S.insert(c);
    }
    
    int maxFreqSize = max(N, Q) + 5;
    vector<int> countF(maxFreqSize, 0);
    for (int c = 1; c <= N; c++){
        countF[f[c]]++;
    }
    
    int globalF = 0;
    for (int i = maxFreqSize-1; i >= 0; i--){
        if(countF[i] > 0) { globalF = i; break; }
    }
    
    while(Q--){
        int i, x;
        cin >> i >> x;
        int old = cowVotes[i-1];
        if(old != x){
            cowVotes[i-1] = x;
            
            int oldFreq = f[old];
            f[old]--;
            int newFreq = f[old];
            countF[oldFreq]--;
            countF[newFreq]++;
            if(newFreq == 0)
                S.erase(old);
            
            if(oldFreq == globalF && countF[oldFreq] == 0){
                for (int j = globalF - 1; j >= 0; j--){
                    if(countF[j] > 0){ globalF = j; break; }
                }
            }
              
            int freqBefore = f[x];
            f[x]++;
            int freqAfter = f[x];
            countF[freqBefore]--;
            countF[freqAfter]++;
            if(freqBefore == 0)
                S.insert(x);
            if(freqAfter > globalF)
                globalF = freqAfter;
        }
        
        if(S.size() < 2){
            cout << 0 << "\n";
            continue;
        }
        
        int gmin = *S.begin();
        int gmax = *S.rbegin();
          
        if(f[gmin] == globalF || f[gmax] == globalF){
            cout << gmax - gmin << "\n";
            continue;
        }
        
        int reqA = globalF - f[gmin];
        int optA = 0;
        
        for(auto rit = S.rbegin(); rit != S.rend(); ++rit){
            int candidate = *rit;
            if(f[candidate] >= reqA){
                optA = candidate - gmin;
                break;
            }
        }
        int reqB = globalF - f[gmax];
        int optB = 0;
        
        for(auto it = S.begin(); it != S.end(); ++it){
            int candidate = *it;
            if(f[candidate] >= reqB){
                optB = gmax - candidate;
                break;
            }
        }
        
        cout << max(optA, optB) << "\n";
    }
    
    return 0;
}
