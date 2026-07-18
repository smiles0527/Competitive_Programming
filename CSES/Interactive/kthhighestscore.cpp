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
const int MOD = 1e9+7;

const ll INF = 2e9, NEG = -1;
int n, k;
vector<ll> fc, sc;

ll getF(int i){
    if(i == 0) return INF;
    if(i == n+1) return NEG;
    if(fc[i] == -2){ cout << "F " << i << "\n" << flush; cin >> fc[i]; }
    return fc[i];
}
ll getS(int i){
    if(i == 0) return INF;
    if(i == n+1) return NEG;
    if(sc[i] == -2){ cout << "S " << i << "\n" << flush; cin >> sc[i]; }
    return sc[i];
}

int main(){
    cin >> n >> k;
    fc.assign(n+2, -2);
    sc.assign(n+2, -2);

    int lo = max(0, k-n), hi = min(k, n);
    ll ans = -1;
    while(lo <= hi){
        int i = (lo+hi)/2, j = k-i;
        ll Fi = getF(i), Fi1 = getF(i+1), Sj = getS(j), Sj1 = getS(j+1);
        if(Fi < Sj1) hi = i-1;          // chosen Finnish too small
        else if(Sj < Fi1) lo = i+1;     // need more from Finland
        else { ans = min(Fi, Sj); break; }
    }

    cout << "! " << ans << "\n" << flush;
    return 0;
}