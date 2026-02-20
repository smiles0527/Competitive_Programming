#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, m;
    cin >> k, m;

    vector<int> ppl(k);

    for (int i = 1; i <= k; i++){
        ppl[i-1] = i;
    }

    for (int i = 0; i < m; i++){
        int r;
        cin >> r; 
        for (int j = 0; j < k; j++){
            if (ppl[j] % r == 0){
                ppl[j] = 0;
            }
        }
    }

    for (int i = 0; i < ppl.size(); i++){
        if (ppl[i] == 0){
            ppl.erase(ppl.begin() + i);
            i--;
        }
    }

    for (int i : ppl){
        cout << i << endl;
    }
    
}   