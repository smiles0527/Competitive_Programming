#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
ll modexp(ll a, ll b) {
    ll res = 1; a %= MOD;
    while(b) { if(b&1) res = (res * a) % MOD; a = (a*a) % MOD; b >>= 1; }
    return res;
}
struct Interval { ll L, R; int v; };
struct Ones { ll L, R; };
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N; int M, Q;
    cin >> N >> M >> Q;
    vector<pair<ll,int>> ev; ev.reserve(2LL*M);
    for(int i=0;i<M;i++){
        ll l, r; cin >> l >> r;
        ev.push_back({l,1});
        if(r+1<=N) ev.push_back({r+1,-1});
    }
    sort(ev.begin(),ev.end());
    vector<Interval> iv;
    ll cur=1; int sum=0; int idx=0;
    while(cur<=N){
        while(idx<ev.size() && ev[idx].first==cur){
            sum += ev[idx].second; idx++;
        }
        int curv = sum & 1;
        ll nxt = (idx<ev.size()? ev[idx].first : N+1);
        ll R = nxt-1; if(R>N) R=N;
        iv.push_back({cur,R,curv});
        cur = nxt;
    }
    vector<Ones> ones;
    for(auto &it: iv) if(it.v==1) ones.push_back({it.L,it.R});
    vector<ll> onesR; onesR.reserve(ones.size());
    for(auto &it: ones) onesR.push_back(it.R);
    for(int qi=0;qi<Q;qi++){
        ll l, r, k; cin >> l >> r >> k;
        ll Lq = r - l + 1;
        ll tot = 0, X = 0;
        int lo = 0, hi = ones.size(), st = ones.size();
        while(lo<hi){
            int mid = (lo+hi)/2;
            if(ones[mid].R >= l){ st = mid; hi = mid; }
            else lo = mid+1;
        }
        for(int i=st;i<ones.size();i++){
            if(ones[i].L > r) break;
            ll Li = max(l, ones[i].L), Ri = min(r, ones[i].R);
            if(Li > Ri) continue;
            ll A = Li - l + 1;
            ll len = Ri - Li + 1;
            ll tseg = min(len, k - X);
            if(tseg <= 0) break;
            ll thresh = k - Lq + A;
            ll j0 = 0;
            if(X < thresh) j0 = min(tseg, thresh - X);
            ll part0 = 0, part1 = 0;
            if(j0 > 0){
                ll e1 = Lq - A + 1, e2 = Lq - A - j0 + 1;
                part0 = (modexp(2,e1) - modexp(2,e2)) % MOD;
                if(part0 < 0) part0 += MOD;
            }
            ll j1 = tseg - j0;
            if(j1 > 0){
                ll e1 = k - X, e2 = k - X - j1;
                part1 = (modexp(2,e1) - modexp(2,e2)) % MOD;
                if(part1 < 0) part1 += MOD;
            }
            tot = (tot + part0 + part1) % MOD;
            X += tseg; if(X >= k) break;
        }
        cout << (tot % MOD + MOD) % MOD << "\n";
    }
    return 0;
}
