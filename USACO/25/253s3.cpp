#include <iostream>
using namespace std;
typedef long long ll;
ll gcd(ll x, ll y){while(y){ll t=x%y;x=y;y=t;}return x;}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);int T;cin>>T;while(T--){ll a,b,c,d;cin>>a>>b>>c>>d;if(c<a||d<b){cout<<-1<<"\n";continue;}if(gcd(a,b)!=gcd(c,d)){cout<<-1<<"\n";continue;}ll cnt=0, x=c, y=d;while(x!=a||y!=b){if(x<a||y<b){cnt=-1;break;}if(x>y){ll t=(x-a)/y; if(t<1)t=1; x-=t*y; cnt+=t;} else if(y>x){ll t=(y-b)/x; if(t<1)t=1; y-=t*x; cnt+=t;} else {cnt=-1; break;}}cout<<cnt<<"\n";}return 0;
    
}
