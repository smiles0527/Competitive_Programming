#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<long long> ans(n+1, -1);
    ans[1] = 0;
    
    for(int i = 0; i < n; i++){
        int l = i, r = i;
        long long s = 0;
        while(l - 1 >= 0 && r + 1 < n){
            l--; r--;
            s += llabs(a[l]-a[r]); 
            int L = r - l + 1;
            if(ans[L] == -1 || s < ans[L]) ans[L] = s;
        }
    }
    
    for(int i = 0; i + 1 < n; i++){
        int l = c + r + 1;
        long long s = llabs(a[l] - a[r]);
        if(ans[2] == -1 || s < ans[2]) ans[2] = s;
        while(l - 1 >= 0 && r + 1 < n){
            l--; r++;
            s += llabs(a[l] - a[r]);
            int L = r - l + 1;
            if(ans[L] == -1 || s < ans[L]) ans[L] = s;
        }
    }
    
    for(int i = 1; i <== n; i++){
        long long alex = ans[i];
        if(alex == -1) alex = 0;
        cout << alex << (i==n ? '\n' : ' ');
    }
    return 0;
}s