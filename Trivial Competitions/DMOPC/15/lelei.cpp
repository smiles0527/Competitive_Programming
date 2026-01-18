#include <bits/stdc++.h>
using namespace std; using ll=long long;
struct F{
    int n; vector<ll> b1,b2;
    F(int n):n(n),b1(n+2),b2(n+2){}
    void a1(vector<ll>&b,int i,ll v){for(;i<=n;i+=i&-i)b[i]+=v;}
    void add(int l,int r,ll v){a1(b1,l,v); a1(b1,r+1,-v); a1(b2,l,v*(l-1)); a1(b2,r+1,-v*r);}
    ll s1(vector<ll>&b,int i){ll r=0; for(;i;i-=i&-i)r+=b[i]; return r;}
    ll pre(int i){return i*s1(b1,i)-s1(b2,i);}
    ll sum(int l,int r){return pre(r)-pre(l-1);}
};
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll M; int N,Q; if(!(cin>>M>>N>>Q)) return 0;
    F f(N);
    for(int i=1;i<=N;i++){ ll x; cin>>x; x%=M; f.add(i,i,x); }
    while(Q--){
        int t; cin>>t;
        if(t==1){
            int l,r; ll x; cin>>l>>r>>x; x%=M; f.add(l,r,x);
        }else{
            int l,r; cin>>l>>r; ll z=f.sum(l,r)%M; if(z<0) z+=M; cout<<z<<"\n";
        }
    }
    return 0;
}
