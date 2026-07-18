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

int n, n1, n2;
vector<ll> x, As, Bs;
vector<int> Am, Bm;

void radix(vector<ull>& a){                          // LSD radix, 4x16-bit passes (keys < 2^60)
    int sz = a.size(); vector<ull> b(sz);
    for(int p = 0; p < 4; p++){
        int sh = p*16; int cnt[65536] = {0};
        for(int i = 0; i < sz; i++) cnt[(a[i]>>sh)&0xFFFF]++;
        int s = 0; for(int j = 0; j < 65536; j++){ int t = cnt[j]; cnt[j] = s; s += t; }
        for(int i = 0; i < sz; i++){ int d = (a[i]>>sh)&0xFFFF; b[cnt[d]++] = a[i]; }
        swap(a, b);
    }
}

static inline ll cntLE(ll X){                        // pairs As[i]+Bs[j] <= X, monotone two-pointer
    ll c = 0; int j = (int)Bs.size()-1, M = (int)As.size();
    const ll* __restrict a = As.data(); const ll* __restrict b = Bs.data();
    for(int i = 0; i < M; i++){ ll t = X - a[i]; while(j >= 0 && b[j] > t) j--; c += j+1; }
    return c;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n; x.resize(n);
    for(auto& v : x) cin >> v;
    n1 = n/2; n2 = n - n1;

    // half subset sums via DP, packed as (sum<<20)|mask, radix-sorted; split into contiguous arrays
    auto build=[&](int base,int cnt,vector<ll>&Sout,vector<int>&Mout){
        int sz = 1<<cnt; vector<ull> key(sz);
        { vector<ll> S(sz,0);
          for(int m=1;m<sz;m++){ int b=__builtin_ctz(m); S[m]=S[m^(1<<b)]+x[base+b]; }
          for(int m=0;m<sz;m++) key[m]=((ull)S[m]<<20)|(ull)m; }
        radix(key);
        Sout.resize(sz); Mout.resize(sz);
        for(int i=0;i<sz;i++){ Sout[i]=(ll)(key[i]>>20); Mout[i]=(int)(key[i]&((1<<20)-1)); }
    };
    build(0,n1,As,Am); build(n1,n2,Bs,Bm);

    auto outPair=[&](ll fA,ll fB){
        ll a=fA&~fB, b=fB&~fA;                        // strip common -> disjoint, both nonempty
        string out;
        auto dump=[&](ll mk){ out+=to_string(__builtin_popcountll(mk)); for(int i=0;i<n;i++) if(mk>>i&1){ out+=' '; out+=to_string(x[i]); } out+='\n'; };
        dump(a); dump(b); cout<<out;
    };

    for(int i=1;i<(int)As.size();i++) if(As[i]==As[i-1]){ outPair((ll)Am[i],(ll)Am[i-1]); return 0; }   // internal half1
    for(int i=1;i<(int)Bs.size();i++) if(Bs[i]==Bs[i-1]){ outPair((ll)Bm[i]<<n1,(ll)Bm[i-1]<<n1); return 0; } // internal half2

    // cross: value-range bisection; one cntLE per level via maintained belowLo
    ll lo=0, hi=As.back()+Bs.back(), belowLo=0;
    while(lo<hi){
        ll mid=lo+(hi-lo)/2;
        ll le=cntLE(mid), lc=le-belowLo;             // pairs in [lo,mid]
        if(lc>mid-lo+1) hi=mid; else { lo=mid+1; belowLo=le; }   // pigeonhole: keep the half guaranteed to hold a collision
    }
    ll v=lo; int got=0; ll fa[2],fb[2];
    for(int i=0;i<(int)As.size() && got<2;i++){
        ll need=v-As[i];
        int p=(int)(lower_bound(Bs.begin(),Bs.end(),need)-Bs.begin());
        if(p<(int)Bs.size() && Bs[p]==need){ fa[got]=Am[i]; fb[got]=Bm[p]; got++; }
    }
    outPair(fa[0]|((ll)fb[0]<<n1), fa[1]|((ll)fb[1]<<n1));
    return 0;
}