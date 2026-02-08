#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static inline void chmax(ll& a, ll b){ if(a < b) a = b; }

struct SegTree{
    int n;
    vector<ll> seg;
    SegTree(int n=0): n(n), seg(n*2, 0) {}
    void range_chmax(int l, int r, ll x){
        l += n; r += n;
        while(l < r){
            if(l & 1) chmax(seg[l++], x);
            if(r & 1) chmax(seg[--r], x);
            l >>= 1; r >>= 1;
        }
    }
    ll operator[](int i) const{
        i += n;
        ll x = 0;
        do chmax(x, seg[i]);
        while(i >>= 1);
        return x;
    }
};

long long max_weights(int N, int M, vector<int> X, vector<int> Y, vector<int> W){
    vector<vector<pair<ll,ll>>> fish(N);
    for(int i=0;i<M;i++) fish[X[i]].push_back({Y[i], W[i]});
    for(auto& v: fish) sort(v.begin(), v.end());

    SegTree up(N+1), down(N+1);
    ll zero = 0;

    for(int x=0;x+1<N;x++){
        for(auto [y,w]: fish[x]) up.range_chmax((int)y+1, N+1, up[(int)y] + w);

        reverse(fish[x+1].begin(), fish[x+1].end());
        for(auto [y,w]: fish[x+1]) down.range_chmax(0, (int)y+1, down[(int)y+1] + w);
        reverse(fish[x+1].begin(), fish[x+1].end());

        ll zero_ = zero;
        zero = down[0];
        down.range_chmax(0, N+1, max(up[N], zero_));
        up.range_chmax(0, N+1, zero_);
    }

    return max({zero, down[0], up[N]});
}
