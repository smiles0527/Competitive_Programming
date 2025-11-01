#include <bits/stdc++.h>
using namespace std; using ll=long long;
int N,M,L;
vector<int> s; vector<uint8_t> z;
void bd(int i,int l,int r){ if((int)s.size()<=i){ s.resize(i+1); z.resize(i+1); }
    if(l==r){ s[i]=1; return; }
    int m=(l+r)>>1, Lc=i<<1, Rc=Lc|1; bd(Lc,l,m); bd(Rc,m+1,r); s[i]=s[Lc]+s[Rc];
}
void app(int i,int l,int r){ s[i]=(r-l+1)-s[i]; z[i]^=1; }
void ps(int i,int l,int r){
    if(!z[i]||l==r) return; int m=(l+r)>>1, Lc=i<<1, Rc=Lc|1; app(Lc,l,m); app(Rc,m+1,r); z[i]=0;
}
void upd(int i,int l,int r,int ql,int qr){
    if(qr<l||r<ql) return;
    if(ql<=l&&r<=qr){ app(i,l,r); return; }
    ps(i,l,r); int m=(l+r)>>1; upd(i<<1,l,m,ql,qr); upd(i<<1|1,m+1,r,ql,qr); s[i]=s[i<<1]+s[i<<1|1];
}
int kth(int i,int l,int r,int k){
    if(l==r) return l;
    ps(i,l,r); int m=(l+r)>>1, Lc=i<<1;
    if(s[Lc]>=k) return kth(Lc,l,m,k);
    return kth(Lc|1,m+1,r,k-s[Lc]);
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>N>>M>>L)) return 0;
    s.resize(4*N+5); z.resize(4*N+5);
    bd(1,1,N);
    while(M--){
        int a,b; cin>>a>>b;
        upd(1,1,N,a,b);
        if(s[1]<L) cout<<"AC?\n";
        else cout<<kth(1,1,N,L)<<"\n";
    }
    return 0;
}
