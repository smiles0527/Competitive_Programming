#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;
const ll NEG = -(ll)4e18;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll a, b; int n; cin >> a >> b >> n;
    vector<ii> v(n);
    for(auto& p : v) cin >> p.f >> p.s;
    sort(v.begin(), v.end(), [](const ii&A,const ii&B){ return A.f-A.s > B.f-B.s; });  // by x-y desc

    // value(S)=sum_S y + top-a (x-y) => optimum splits at a cut: left -> programmers (by x), right -> artists (by y)
    vector<ll> leftA(n+1, NEG), rightB(n+1, NEG);
    { priority_queue<ll,vector<ll>,greater<>> h; ll s=0; leftA[0]=(a==0?0:NEG);     // top-a x among first c
      for(int c=1;c<=n;c++){ ll x=v[c-1].f;
        if((ll)h.size()<a){ h.push(x); s+=x; } else if(a>0 && x>h.top()){ s+=x-h.top(); h.pop(); h.push(x); }
        leftA[c]=((ll)h.size()==a)? s : NEG; } }
    { priority_queue<ll,vector<ll>,greater<>> h; ll s=0; rightB[n]=(b==0?0:NEG);    // top-b y among [c,n)
      for(int c=n-1;c>=0;c--){ ll y=v[c].s;
        if((ll)h.size()<b){ h.push(y); s+=y; } else if(b>0 && y>h.top()){ s+=y-h.top(); h.pop(); h.push(y); }
        rightB[c]=((ll)h.size()==b)? s : NEG; } }

    ll ans=NEG;
    for(int c=0;c<=n;c++) if(leftA[c]>NEG/2 && rightB[c]>NEG/2) ans=max(ans, leftA[c]+rightB[c]);
    cout << ans << "\n";
}