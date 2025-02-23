#include <bits/stdc++.h>
using namespace std;




inline void computeB(const int a[], int n, vector<int>& b) {
    vector<int> temp;
    temp.reserve(n);
    int cur = 0; 
    for (int i = n - 1; i >= 0; i--) {
        if(a[i] >= cur) {
            temp.push_back(a[i]);
            cur = a[i];
        }
    }
    int t = temp.size();
    b.resize(t);
    for (int i = 0; i < t; i++) {
        b[i] = temp[t - 1 - i];
    }
}
 


inline bool lexGreaterB(const vector<int>& b1, const vector<int>& b2) {
    int m = min(b1.size(), b2.size());
    for (int i = 0; i < m; i++) {
        if(b1[i] != b2[i])
            return b1[i] > b2[i];
    }
    return b1.size() > b2.size();
}
 



inline void simulateMove(const int orig[], int n, int i, int j, int cand[]) {
    if(i > 0)
        memcpy(cand, orig, i * sizeof(int));         
    cand[i] = orig[j];                                 
    if(j - i > 0)
        memcpy(cand + i + 1, orig + i, (j - i) * sizeof(int));  
    if(n - j - 1 > 0)
        memcpy(cand + j + 1, orig + j + 1, (n - j - 1) * sizeof(int)); 
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; 
    cin >> T;
    for (int t = 0; t < T; t++){
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
 
        
        vector<int> bestB;
        {
            
            vector<int> temp_a = a;
            computeB(temp_a.data(), n, bestB);
        }
 
        
        vector<int> S(n);
        S[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--){
            S[i] = max(a[i], S[i + 1]);
        }
 
        
        vector<int> cand(n);
        vector<int> candB;
 
        
        for (int i = 0; i < n - 1; i++){
            if(a[i] < S[i + 1]) {  
                int candidateVal = S[i + 1];
                int jCandidate = -1;
                
                for (int j = n - 1; j > i; j--){
                    if(a[j] == candidateVal) {
                        jCandidate = j;
                        break;
                    }
                }
                if(jCandidate == -1) continue; 
                simulateMove(a.data(), n, i, jCandidate, cand.data());
                computeB(cand.data(), n, candB);
                if( lexGreaterB(candB, bestB) ) {
                    bestB = candB;
                }
            }
        }
 
        for (int i = 0; i < bestB.size(); i++){
            cout << bestB[i] << (i + 1 == bestB.size() ? "\n" : " ");
        }
    }
    return 0;
}
