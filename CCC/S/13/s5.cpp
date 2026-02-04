#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, ans=0;
    cin >> n;
    while(n > 1){
        long long d=0;
        for(long long i=2;i*i<=n;i++) if(n%i==0){ d=i; break; }
        if(!d) d=n;
        long long b=n/d;
        n-=b;
        ans+=n/b;
    }
    cout << ans << "\n";
    return 0;
}
