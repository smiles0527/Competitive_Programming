#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    S = " " + S; 
 
    
    vector<int> nextDiff(N+2, N+1);
    nextDiff[N] = N+1;
    for(int i = N - 1; i >= 1; i--){
        if(S[i] == S[i+1])
            nextDiff[i] = nextDiff[i+1];
        else
            nextDiff[i] = i+1;
    }
 
    
    vector<vector<int>> pos(26);
    for (int i = 1; i <= N; i++){
        pos[S[i] - 'a'].push_back(i);
    }
 
    while(Q--){
        int l, r;
        cin >> l >> r;
 
        long long ans = -1;
        
        for (int L = 0; L < 26; L++){
            
            
            int base;
            if(S[l] - 'a' == L) {
                if(nextDiff[l] > r) continue; 
                base = nextDiff[l];
            } else {
                base = l;
            }
 
            
            auto &vec = pos[L];
            auto itLow = lower_bound(vec.begin(), vec.end(), l);
            auto itHigh = upper_bound(vec.begin(), vec.end(), r);
            if(itLow == itHigh) continue; 
            if(distance(itLow, itHigh) < 2) continue; 
 
            
            int lastOccurrence = *(itHigh - 1);
 
            
            auto itValid = lower_bound(itLow, itHigh, base);
            
            if(itValid == itHigh || *itValid == lastOccurrence){
                if(itValid == itLow) continue; 
                itValid--;
            }
 
            
            auto startIt = lower_bound(itLow, itHigh, base);
            auto endIt = itHigh - 1; 
 
            if(startIt >= endIt) continue;
 
            
            
            double target = (base + lastOccurrence) / 2.0;
            auto candidateIt = lower_bound(startIt, endIt, (int)target);
 
            long long candidateVal = -1;
            auto checkCandidate = [&](auto it) {
                if(it >= startIt && it < endIt){
                    int j = *it;
                    long long val = (long long)(j - base) * (lastOccurrence - j);
                    candidateVal = max(candidateVal, val);
                }
            };
 
            if(candidateIt != endIt)
                checkCandidate(candidateIt);
            if(candidateIt != startIt){
                auto prevIt = candidateIt;
                prevIt--;
                checkCandidate(prevIt);
            }
 
            ans = max(ans, candidateVal);
        }
 
        cout << ans << "\n";
    }
 
    return 0;
}
