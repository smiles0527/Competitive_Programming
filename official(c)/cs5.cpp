#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
const int MODVAL = 1000000+3;
const ll NEG_INF = -1e18;
 
struct SegTree {
    int n;
    vector<ll> seg, lazy;
    SegTree(int n): n(n) {
        seg.assign(4*n, NEG_INF);
        lazy.assign(4*n, 0);
    }
    void pushDown(int idx, int l, int r) {
        if(lazy[idx]!=0) {
            int mid=(l+r)/2;
            seg[idx*2] += lazy[idx];
            seg[idx*2+1] += lazy[idx];
            lazy[idx*2] += lazy[idx];
            lazy[idx*2+1] += lazy[idx];
            lazy[idx] = 0;
        }
    }
    void updateRange(int idx, int l, int r, int ql, int qr, ll val) {
        if(ql>r || qr<l)return;
        if(ql<=l && r<=qr) {
            seg[idx] += val;
            lazy[idx] += val;
            return;
        }
        pushDown(idx,l,r);
        int mid=(l+r)/2;
        updateRange(idx*2,l,mid,ql,qr,val);
        updateRange(idx*2+1,mid+1,r,ql,qr,val);
        seg[idx]=max(seg[idx*2], seg[idx*2+1]);
    }
    void updatePoint(int idx, int l, int r, int pos, ll val) {
        if(l==r) {
            seg[idx] = val;
            return;
        }
        pushDown(idx,l,r);
        int mid=(l+r)/2;
        if(pos<=mid) updatePoint(idx*2,l,mid,pos,val);
        else updatePoint(idx*2+1,mid+1,r,pos,val);
        seg[idx]=max(seg[idx*2], seg[idx*2+1]);
    }
    ll query(int idx, int l, int r, int ql, int qr) {
        if(ql>r || qr<l)return NEG_INF;
        if(ql<=l && r<=qr)return seg[idx];
        pushDown(idx,l,r);
        int mid=(l+r)/2;
        return max(query(idx*2,l,mid,ql,qr), query(idx*2+1,mid+1,r,ql,qr));
    }
    void updRange(int l, int r, ll val) { updateRange(1,0,n-1,l,r,val); }
    void updPoint(int pos, ll val) { updatePoint(1,0,n-1,pos,val); }
    ll qry(int l, int r) { return query(1,0,n-1,l,r); }
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int Q; cin >> Q;
    SegTree seg(MODVAL);
    vector<ll> base(MODVAL);
    for (int i = 0; i < MODVAL; i++){
        base[i] = i - 1;
        seg.updPoint(i, NEG_INF);
    }
    vector<pair<int,int>> tasks;
    tasks.reserve(Q);
    vector<ll> Tval(MODVAL, 0);
    ll totalTime = 0, ans = 0;
    for (int qi = 0; qi < Q; qi++){
        char typ; cin >> typ;
        if(typ=='A'){
            ll s_, t_;
            cin >> s_ >> t_;
            int s = (int)((s_ + ans) % MODVAL);
            int t = (int)((t_ + ans) % MODVAL);
            if(s < 1) s = 1;
            if(t < 1) t = 1;
            tasks.push_back({s,t});
            totalTime += t;
            if(Tval[s] == 0){
                seg.updPoint(s, seg.qry(s,s)==NEG_INF ? (s - 1) : seg.qry(s,s));
                seg.updPoint(s, s - 1);
            }
            Tval[s] += t;
            if(s+1 < MODVAL) seg.updRange(s+1, MODVAL-1, -t);
        } else {
            ll i_; cin >> i_;
            int i = (int)((i_ + ans) % MODVAL);
            if(i < 1) i = 1;
            int idx = i - 1;
            int s = tasks[idx].first, t = tasks[idx].second;
            tasks[idx] = {0,0};
            totalTime -= t;
            Tval[s] -= t;
            if(Tval[s] == 0){
                seg.updPoint(s, NEG_INF);
            }
            if(s+1 < MODVAL) seg.updRange(s+1, MODVAL-1, t);
        }
        ll bestCandidate = seg.qry(0, MODVAL-1);
        if(bestCandidate < 0) bestCandidate = 0;
        ans = totalTime + bestCandidate;
        cout << ans << "\n";
    }
    return 0;
}
