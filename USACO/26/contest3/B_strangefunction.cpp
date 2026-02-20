#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--){
        string s; cin >> s;
        int n = (int)s.size();

        int bin = 1;
        for(char c: s) if(c!='0' && c!='1'){ bin = 0; break; }

        long long m = 0, h = 0;
        
        for(int i=0;i<n;i++){
            int b = (bin ? (s[i]-'0') : ((s[i]-'0')&1));
            m = (m*2 + b) % MOD;
            if(i+1<n) h = (h*2 + b) % MOD;
        }

        long long ans = (m + h + (bin?0:1)) % MOD;
        cout << ans << "\n";
    }
    return 0;
}