#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using i128=__int128_t;

struct Nd{
    Nd*l,*r; int pr; i128 k; ll v; int idx,sz; long long gsum; ll fl,llv; int fi,li;
    Nd(i128 K,ll V,int I,int P):l(0),r(0),pr(P),k(K),v(V),idx(I),sz(1),gsum(0),fl(V),llv(V),fi(I),li(I){}
};
mt19937 rng(712367);

inline long long gap(ll a,int ia,ll b,int ib){ if(a<0) return 0; long long g=(long long)(b-a)-(ib-ia); return g>0?g:0; }
inline int SZ(Nd*t){ return t?t->sz:0; }
inline long long G(Nd*t){ return t?t->gsum:0; }
inline void firstlast(Nd*t,ll&fv,int&fi,ll&lv,int&li){
    if(!t){ fv=-1; fi=-1; lv=-1; li=-1; return; }
    fv=t->fl; fi=t->fi; lv=t->llv; li=t->li;
}
inline void pu(Nd*t){
    if(!t) return;
    t->sz = 1 + SZ(t->l) + SZ(t->r);
    ll lf,lr; int lfi,lri; firstlast(t->l,lf,lfi,lr,lri);
    ll rf,rr; int rfi,rri; firstlast(t->r,rf,rfi,rr,rri);
    t->fl = (t->l? lf : t->v); t->fi = (t->l? lfi : t->idx);
    t->llv = (t->r? rr : t->v); t->li = (t->r? rri : t->idx);
    long long gl = G(t->l), gr = G(t->r);
    long long glx = t->l? gap(lr,lri,t->v,t->idx):0;
    long long grx = t->r? gap(t->v,t->idx,rf,rfi):0;
    t->gsum = gl + gr + glx + gr;
    t->gsum = gl + gr + glx + grx;
}
Nd* mg(Nd*a,Nd*b){
    if(!a||!b) return a?a:b;
    if(a->pr<b->pr){ a->r=mg(a->r,b); pu(a); return a; }
    b->l=mg(a,b->l); pu(b); return b;
}
void sp(Nd*t,i128 k,Nd*&a,Nd*&b){
    if(!t){ a=b=0; return; }
    if(k<t->k){ sp(t->l,k,a,t->l); b=t; pu(b); }
    else{ sp(t->r,k,t->r,b); a=t; pu(a); }
}
Nd* ins(Nd*t,Nd* x){
    if(!t) return x;
    if(x->pr<t->pr){
        sp(t,x->k,x->l,x->r); pu(x); return x;
    }
    if(x->k<t->k) t->l=ins(t->l,x); else t->r=ins(t->r,x);
    pu(t); return t;
}
Nd* er(Nd*t,i128 k){
    if(!t) return 0;
    if(k==t->k){ Nd* u=mg(t->l,t->r); return u; }
    if(k<t->k) t->l=er(t->l,k); else t->r=er(t->r,k);
    pu(t); return t;
}
Nd* minnode(Nd*t){ while(t->l) t=t->l; return t; }
Nd* maxnode(Nd*t){ while(t->r) t=t->r; return t; }
Nd* pred(Nd
