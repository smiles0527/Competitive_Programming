#include <bits/stdc++.h>
using namespace std;

struct Node {
    int lo, hi;
    Node(int l=0, int h=1000000000): lo(l), hi(h) {}
};
struct Seg {
    int n;
    vector<Node> t, lz;
    Seg(int n): n(n), t(4*n), lz(4*n) {}
    static inline void clamp_pair(Node& x, const Node& y) {
        x.lo = min(max(x.lo, y.lo), y.hi);
        x.hi = min(max(x.hi, y.lo), y.hi);
    }
    void apply(int p, const Node& v) {
        clamp_pair(t[p], v);
        clamp_pair(lz[p], v);
    }
    void push(int p) {
        if (lz[p].lo!=0 || lz[p].hi!=1000000000) {
            apply(p<<1, lz[p]);
            apply(p<<1|1, lz[p]);
            lz[p] = Node();
        }
    }
    void upd(int p, int l, int r, int ql, int qr, const Node& v) {
        if (qr<l || r<ql) return;
        if (ql<=l && r<=qr) { apply(p, v); return; }
        push(p);
        int m=(l+r)>>1;
        upd(p<<1,l,m,ql,qr,v);
        upd(p<<1|1,m+1,r,ql,qr,v);
    }
    void finalize(int p, int l, int r, vector<int>& out) {
        if (l==r) { out[l]=t[p].lo; return; }
        push(p);
        int m=(l+r)>>1;
        finalize(p<<1,l,m,out);
        finalize(p<<1|1,m+1,r,out);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    if(!(cin>>n>>k)) return 0;
    Seg seg(n);
    for(int i=0;i<k;i++){
        int op,L,R,h;
        cin>>op>>L>>R>>h;
        if(op==1){
            seg.upd(1,0,n-1,L,R,Node(h,1000000000));
        }else{
            seg.upd(1,0,n-1,L,R,Node(0,h));
        }
    }
    vector<int> ans(n);
    seg.finalize(1,0,n-1,ans);
    for(int i=0;i<n;i++) cout<<ans[i]<<"\n";
    return 0;
}
