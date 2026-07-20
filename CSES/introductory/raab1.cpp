#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T; cin >> T;
    while(T--){
        int n,a,b; cin >> n >> a >> b;
        int m=a+b, t=n-m;
        if(t<0 || (m>0 && (a==0||b==0))){ cout<<"NO\n"; continue; }
        cout<<"YES\n";
        for(int i=1;i<=n;i++) cout<<i<<" \n"[i==n];   // A: 1..n
        for(int i=1;i<=m;i++) cout<<((i-1+a)%m)+1<<' ';// B contested: shift by a
        for(int v=m+1;v<=n;v++) cout<<v<<" \n"[v==n];  // B ties: m+1..n
        if(m==n) cout<<"\n";                            // no tie block printed newline
    }	

	return 0;
}
