#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    
    string s(n, ' ');
    for(int i = 0; i < n; i++) cin >> s[i];

    int l = 0; int in = 0; int best = 0; int total = 0;
    for(int r = 0; r < n; r++){
        if(s[r] == 'P'){
            in++; total++;
        }
        while(in > 1){
            if(s[l] == 'P'){
                in--;
            }
            l++;
        }
        best = max(best, r-l+1);
    }
    cout << (total ? best : n-1) << '\n';
}
