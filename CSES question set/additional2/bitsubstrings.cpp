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

// const ll M1 = 998244353, M2 = 1004535809, G = 3;

// ll pw(ll a, ll b, ll m){ ll r=1; a%=m; while(b){ if(b&1) r=(__int128)r*a%m; a=(__int128)a*a%m; b>>=1; } return r; }

// void ntt(vector<ll>& a, ll mod, bool inv){
//     int n=a.size();
//     for(int i=1,j=0;i<n;i++){ int bit=n>>1; for(;j&bit;bit>>=1) j^=bit; j^=bit; if(i<j) swap(a[i],a[j]); }
//     for(int len=2;len<=n;len<<=1){
//         ll w=pw(G, (mod-1)/len, mod); if(inv) w=pw(w, mod-2, mod);
//         for(int i=0;i<n;i+=len){ ll wn=1;
//             for(int k=0;k<len/2;k++){ ll u=a[i+k], v=(__int128)a[i+k+len/2]*wn%mod;
//                 a[i+k]=(u+v)%mod; a[i+k+len/2]=(u-v+mod)%mod; wn=(__int128)wn*w%mod; } }
//     }
//     if(inv){ ll ni=pw(n, mod-2, mod); for(auto& x:a) x=(__int128)x*ni%mod; }
// }

// vector<ll> mul(vector<ll> a, vector<ll> b, ll mod){
//     int rs=a.size()+b.size()-1, sz=1; while(sz<rs) sz<<=1;
//     a.resize(sz); b.resize(sz); ntt(a,mod,false); ntt(b,mod,false);
//     for(int i=0;i<sz;i++) a[i]=(__int128)a[i]*b[i]%mod;
//     ntt(a,mod,true); a.resize(rs); return a;
// }

using cd = complex<double>;
const double PI = acos(-1.0);

void fft(vector<cd>& a, bool inv) {
    int n = a.size();

    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        cd wlen(cos(ang), sin(ang));

        for(int i = 0; i < n; i += len) {
            cd w = 1;
            for(int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if(inv) {
        for(cd& x : a) x /= n;
    }
}

vector<ll> mul(const vector<ll>& a, const vector<ll>& b) {
    int rs = a.size() + b.size() - 1;
    int sz = 1;
    while(sz < rs) sz <<= 1;

    vector<cd> fa(sz), fb(sz);
    for(int i = 0; i < (int)a.size(); i++) fa[i] = a[i];
    for(int i = 0; i < (int)b.size(); i++) fb[i] = b[i];

    fft(fa, false);
    fft(fb, false);

    for(int i = 0; i < sz; i++) fa[i] *= fb[i];

    fft(fa, true);

    vector<ll> res(rs);
    for(int i = 0; i < rs; i++) res[i] = llround(fa[i].real());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();

    int S = count(s.begin(), s.end(), '1');
    vector<ll> cnt(S + 1, 0);

    int p = 0;
    cnt[0]++;

    for(char ch : s) {
        if(ch == '1') p++;
        cnt[p]++;
    }

    vector<ll> ans(n + 1, 0);

    for(ll x : cnt) ans[0] += x * (x - 1) / 2;

    if(S) {
        vector<ll> A = cnt;
        vector<ll> B(cnt.rbegin(), cnt.rend());

        vector<ll> r = mul(A, B);

        for(int k = 1; k <= S; k++) {
            ans[k] = r[S + k];
        }
    }

    // if(S >= 1){
    //     vector<ll> A=cnt, B(cnt.rbegin(), cnt.rend());
    //     vector<ll> r1=mul(A,B,M1), r2=mul(A,B,M2);
    //     ll inv1=pw(M1%M2, M2-2, M2);
    //     for(int k=1;k<=min((ll)n,(ll)S);k++){
    //         int idx = S + k;
    //         if(idx >= (int)r1.size()) break;
    //         ll x1=r1[idx], x2=r2[idx];
    //         ll t=((x2-x1)%M2+M2)%M2; t=(__int128)t*inv1%M2;
    //         ll val=(x1 + (__int128)t*M1)% (M1*M2);
    //         ans[k]=val;
    //     }
    // }

    string out;
    out.reserve((n + 1) * 12);

    for(int k = 0; k <= n; k++) {
        out += to_string(ans[k]);
        out += ' ';
    }

    cout << out << '\n';
    return 0;
}