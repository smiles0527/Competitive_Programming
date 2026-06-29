#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, k;
    cin >> n >> k;

    auto colorCnt = [&](int col)->vi{          // ways to place j non-attacking bishops on one color
        vector<int> sz;
        for(int d=0; d<=2*n-2; d++) if((d&1)==col) sz.pb(min<int>(d, 2*n-2-d)+1);
        sort(sz.begin(), sz.end());
        int K = min<ll>(k, (ll)sz.size());
        vi f(K+1, 0); f[0]=1;
        int cntp=0;
        for(int s : sz){
            cntp++;
            for(int j=min(K,cntp); j>=1; j--){     // j-th bishop on size-s diagonal
                ll factor = s-(j-1);
                if(factor<=0) continue;            // no free perpendicular slot
                f[j]=(f[j] + f[j-1]*(factor%MOD))%MOD;
            }
        }
        return f;
    };

    vi c0 = colorCnt(0), c1 = colorCnt(1);
    ll ans=0;
    for(int a=0; a<(int)c0.size(); a++){
        int b=k-a;
        if(b>=0 && b<(int)c1.size()) ans=(ans + c0[a]*c1[b])%MOD;
    }
    cout << ans << '\n';
    return 0;
}