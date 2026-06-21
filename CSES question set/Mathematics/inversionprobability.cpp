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

// typedef __int128 lll;
// lll gcdll(lll a, lll b) { while (b) { lll t = a % b; a = b; b = t; } return a; }

struct Big { vector<uint32_t> d; void norm(){ while(!d.empty()&&d.back()==0) d.pop_back(); } bool zero() const { return d.empty(); } };
Big fromu(uint64_t x){ Big b; while(x){ b.d.pb((uint32_t)(x&0xffffffffu)); x>>=32; } return b; }
int cmpB(const Big&a,const Big&b){ if(a.d.size()!=b.d.size()) return a.d.size()<b.d.size()?-1:1;
    for(int i=(int)a.d.size()-1;i>=0;i--) if(a.d[i]!=b.d[i]) return a.d[i]<b.d[i]?-1:1; return 0; }
Big addB(const Big&a,const Big&b){ Big r; uint64_t c=0; size_t n=max(a.d.size(),b.d.size());
    for(size_t i=0;i<n||c;i++){ uint64_t s=c; if(i<a.d.size())s+=a.d[i]; if(i<b.d.size())s+=b.d[i];
        r.d.pb((uint32_t)(s&0xffffffffu)); c=s>>32; } r.norm(); return r; }
Big subB(const Big&a,const Big&b){ Big r; int64_t c=0;                 // a>=b
    for(size_t i=0;i<a.d.size();i++){ int64_t s=(int64_t)a.d[i]-c-(i<b.d.size()?b.d[i]:0);
        if(s<0){ s+=(1LL<<32); c=1; } else c=0; r.d.pb((uint32_t)s); } r.norm(); return r; }
Big mulS(const Big&a, uint64_t m){ Big r; uint64_t c=0;
    for(size_t i=0;i<a.d.size();i++){ unsigned __int128 cur=(unsigned __int128)a.d[i]*m+c;
        r.d.pb((uint32_t)(cur&0xffffffffu)); c=(uint64_t)(cur>>32); }
    while(c){ r.d.pb((uint32_t)(c&0xffffffffu)); c>>=32; } r.norm(); return r; }
uint64_t modS(const Big&a, uint64_t m){ uint64_t r=0;
    for(int i=(int)a.d.size()-1;i>=0;i--){ unsigned __int128 cur=((unsigned __int128)r<<32)|a.d[i]; r=(uint64_t)(cur%m); } return r; }
Big divS(const Big&a, uint64_t m){ Big r; r.d.resize(a.d.size()); uint64_t rem=0;
    for(int i=(int)a.d.size()-1;i>=0;i--){ unsigned __int128 cur=((unsigned __int128)rem<<32)|a.d[i];
        r.d[i]=(uint32_t)(cur/m); rem=(uint64_t)(cur%m); } r.norm(); return r; }
void shl1(Big&a){ uint32_t c=0; for(size_t i=0;i<a.d.size();i++){ uint32_t nc=a.d[i]>>31; a.d[i]=(a.d[i]<<1)|c; c=nc; } if(c) a.d.pb(c); }
int bitlen(const Big&a){ if(a.zero())return 0; int hb=(int)a.d.size()-1; uint32_t t=a.d[hb]; int b=0; while(t){b++;t>>=1;} return hb*32+b; }
int getbit(const Big&a,int i){ return (a.d[i>>5]>>(i&31))&1; }
uint64_t gsmall(uint64_t a,uint64_t b){ while(b){ uint64_t t=a%b; a=b; b=t; } return a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> r(n);
    for (auto& v : r) cin >> v;

//  double ans = 0;
//  long double ans = 0;
//  __float128 ans = 0;                   // 113-bit mantissa: error << 6-decimal boundary
//  lll N = 0, D = 1;                     // exact running sum N/D (overflowed __int128 on big n)
    Big N = fromu(0), D = fromu(1);        // exact running sum N/D, arbitrary precision
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++) {
            ll ra = r[a], rb = r[b];
            // count pairs (u,v), u in [1,ra], v in [1,rb], u>v
            // sum over v=1..min(ra-1,rb) of (ra - v)
            ll hi = min(ra - 1, rb);
            ll num = 0;
            if (hi >= 1) {
                // sum_{v=1}^{hi} (ra - v) = hi*ra - hi(hi+1)/2
                num = hi * ra - hi * (hi + 1) / 2;
            }
//          ans += (double)num / (double)(ra * rb);
//          ans += (long double)num / (long double)(ra * rb);
//          ans += (__float128)num / (__float128)(ra * rb);
            if (num == 0) continue;
//          lll p = num, q = (lll)ra * rb;
//          lll g = gcdll(p, q); p /= g; q /= g;          // reduce term
//          lll gd = gcdll(D, q);                          // lcm-combine N/D + p/q
//          lll nd = D / gd * q;
//          N = N * (nd / D) + p * (nd / q);
//          D = nd;
//          lll gg = gcdll(N, D); if (gg > 1) { N /= gg; D /= gg; }   // keep D minimal
            uint64_t p = (uint64_t)num, q = (uint64_t)ra * rb;
            uint64_t g = gsmall(modS(D, q), q);           // gcd(D,q), small since q<=1e4
            Big Dg = divS(D, g);                          // D/g exact
            N = addB(mulS(N, q / g), mulS(Dg, p));        // N*(q/g) + p*(D/g)
            D = mulS(Dg, q);                              // (D/g)*q = lcm(D,q)
        }

//  cout << fixed << setprecision(6) << (double)ans << '\n';
//  ll micros = (ll)(ans * (__float128)1000000 + (__float128)0.5);   // round half up
//  ll ip = micros / 1000000, fp = micros % 1000000;
//  char tail[8];
//  snprintf(tail, sizeof(tail), "%06lld", fp);
//  cout << ip << '.' << tail << '\n';

//  lll ip = N / D, R = N % D, frac = 0;                   // exact 6-digit long division (int128)
//  for (int i = 0; i < 6; i++) { R *= 10; frac = frac * 10 + R / D; R %= D; }
//  lll twoR = R * 2;
//  bool up = (twoR > D) || (twoR == D && (frac & 1));     // half-even
//  if (up) { if (++frac == 1000000) { frac = 0; ip++; } }
//  cout << (ll)ip << '.' << setw(6) << setfill('0') << (ll)frac << '\n';

    Big M = mulS(N, 1000000ULL);                           // floor(E*1e6) = M / D, plus remainder R
    Big R = fromu(0); uint64_t Q = 0;
    for (int i = bitlen(M) - 1; i >= 0; i--) {             // binary long division
        shl1(R);
        if (getbit(M, i)) R = addB(R, fromu(1));
        Q <<= 1;
        if (cmpB(R, D) >= 0) { R = subB(R, D); Q |= 1; }
    }
    int c2 = cmpB(mulS(R, 2), D);                          // 2R vs D  -> half-even
    if (c2 > 0 || (c2 == 0 && (Q & 1))) Q++;
    uint64_t ip = Q / 1000000ULL, fp = Q % 1000000ULL;
    cout << ip << '.' << setw(6) << setfill('0') << fp << '\n';
    return 0;
}