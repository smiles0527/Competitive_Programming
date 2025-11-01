#include <bits/stdc++.h>
using namespace std; using ll=long long;
struct T{ ll k,s; int v,m; uint32_t p; T*l,*r; T(ll K,int V,uint32_t P):k(K),s(V),v(V),m(V),p(P),l(0),r(0){} };
int M(T*t){return t?t->m:0;} ll S(T*t){return t?t->s:0;}
void U(T*t){t->m=max(t->v,max(M(t->l),M(t->r))); t->s=t->v+S(t->l)+S(t->r);}
void sp(T*t,ll k,T*&a,T*&b){ if(!t){a=b=0;return;} if(t->k<=k){ sp(t->r,k,t->r,b); a=t; U(a);} else { sp(t->l,k,a,t->l); b=t; U(b);} }
T* mg(T*a,T*b){ if(!a||!b) return a?a:b; if(a->p<b->p){ a->r=mg(a->r,b); U(a); return a;} b->l=mg(a,b->l); U(b); return b; }
void setv(T*&t,ll k,int v,mt19937&g){ T *a,*b,*c; sp(t,k,a,b); sp(a,k-1,a,c); if(c){ c->v=v; U(c);} else c=new T(k,v,g()); t=mg(mg(a,c),b); }
ll qsum(T*&t,ll L,ll R){ T *a,*b,*c; sp(t,R,a,b); sp(a,L-1,a,c); ll z=S(c); t=mg(mg(a,c),b); return z; }
int qmax(T*&t,ll L,ll R){ T *a,*b,*c; sp(t,R,a,b); sp(a,L-1,a,c); int z=M(c); t=mg(mg(a,c),b); return z; }
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    ll N; int Q; if(!(cin>>N>>Q)) return 0; mt19937 g(712367); T* rt=0; ll z=0;
    while(Q--){ char t; cin>>t;
        if(t=='C'){ ll x,v; cin>>x>>v; x^=z; v^=z; setv(rt,x,(int)v,g); }
        else if(t=='S'){ ll l,r; cin>>l>>r; l^=z; r^=z; if(l>r) swap(l,r); z=qsum(rt,l,r); cout<<z<<"\n"; }
        else { ll l,r; cin>>l>>r; l^=z; r^=z; if(l>r) swap(l,r); int a=qmax(rt,l,r); cout<<a<<"\n"; z=a; }
    }
    return 0;
}
