#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;

static inline i128 f(const vector<ll>& a, const vector<ll>& b, i128 dd, i128 y  ){
    i128 s = 0;
    int n = (int)a.size();
    for(int i=0;i<n;i++){
        i128 ai = (i128)a[i], bi = (i128)b[i];
        i128 v1 = y - bi; i128 v2 = ai - dd - y;
        i128 cur = 0;
        if(v1 > cur) cur = v1;
        if(v2 > cur) cur = v2;
        s += cur;
    }
    return s;
}

static inline bool chk(const vector<ll>& a, const vector<ll>& b, ll d, ll Kll){
    i128 K = (i128)Kll;
    i128 dd = (i128)d;
    const i128 INF = (i128)4000000000000000000LL;

    i128 mn = INF, mx = -INF;
    int n = (int)a.size();
    for(int i=0;i<n;i++){
        i128 x = (i128)a[i] - dd;
        mn = min(mn, min(x, (i128)b[i]));
        mx = max(mx, max(x, (i128)b[i]));
    }

    i128 L = mn - K - 5, R = mx + K + 5;

    while(L < R){
        i128 m = L + (R-L) / 2;
        if(f(a, b, dd, m) <= f(a, b, dd,m+1)) R = m;
        else L = m + 1;
    }

    return f(a,b,dd,L) <= K;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--){
        int N; ll K; cin >> N >> K;
        vector<ll> a(N), b(N);
        for(auto &x:a) cin >> x;
        for(auto &x:b) cin >> x;

        ll mxA = a[0], mnB = b[0];
        for(int i=0;i<N;i++){
            mxA = max(mxA, a[i]);
            mnB = min(mnB, b[i]);
        }

        i128 hi = (i128)mxA - (i128)mnB;
        i128 lo = hi - (i128)2 * (i128)K;

        ll L = (ll)lo, R = (ll)hi;
        while(L < R){
            ll m = L + (R - L) / 2;
            if(chk(a,b,m,K)) R = m;
            else L = m + 1;
        }
        cout << L << "\n";
    }
    return 0;
}
