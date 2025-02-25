#include <bits/stdc++.h>
using namespace std;

vector<int> computeB(const vector<int>& a) {
    int n = a.size();
    vector<int> temp;
    temp.reserve(n);
    int cur = 0; 
    for (int i = n - 1; i >= 0; i--) {
        if(a[i] >= cur) {
            temp.push_back(a[i]);
            cur = a[i];
        }
    }
    reverse(temp.begin(), temp.end());
    return temp;
}
 
bool lexGreater(const vector<int>& A, const vector<int>& B) {
    int m = min(A.size(), B.size());
    for (int i = 0; i < m; i++){
        if (A[i] != B[i])
            return A[i] > B[i];
    }
    return A.size() > B.size();
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; 
    cin >> T;
    while(T--){
        int n; 
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> b0 = computeB(a);
        
        
        vector<int> S(n);
        S[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--){
            S[i] = max(a[i], S[i + 1]);
        }
        
        int candidateIndex = -1;
        for (int i = 0; i < n - 1; i++){
            if(a[i] < S[i+1]){
                candidateIndex = i;
                break;
            }
        }
        
        vector<int> bestB = b0;
        if(candidateIndex != -1) {
            int candidateVal = S[candidateIndex+1];
            int jCandidate = -1;
            for (int j = n - 1; j > candidateIndex; j--){
                if(a[j] == candidateVal) {
                    jCandidate = j;
                    break;
                }
            }
            if(jCandidate != -1) {
                vector<int> candidate = a;
                int temp = candidate[jCandidate];
                
                for (int k = jCandidate; k > candidateIndex; k--) {
                    candidate[k] = candidate[k-1];
                }
                candidate[candidateIndex] = temp;
                vector<int> b1 = computeB(candidate);
                if( lexGreater(b1, bestB) )
                    bestB = b1;
            }
        }
        
        for (int i = 0; i < bestB.size(); i++){
            cout << bestB[i] << (i + 1 == bestB.size() ? "\n" : " ");
        }
    }
    return 0;
}
