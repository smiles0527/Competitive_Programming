#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct T{
    ll L,R,S; int sz,pr; T *l,*r,*p;
    T(ll a,ll b):L(a),R(b),S(b-a+1),sz(1),pr((rand()<<16)^rand()),l(0),r(0),p(0){}
};
inline ll len(T* x){ return x? x->R-x->L+1:0; }
inline ll sm(T* x){ return x? x->S:0; }
inline int sz(T* x){ return x? x->sz:0; }
inline void up(T* x){
    if(!x) return;
    x->sz=1+sz(x->l)+sz(x->r);
    x->S=len(x)+sm(x->l)+sm(x->r);
    if(x->l) x->l->p=x;
    if(x->r) x->r->p=x;
}
T* mg(T* a,T* b){
    if(!a) return b; if(!b) return a;
    if(a->pr>b->pr){
        a->r=mg(a->r,b); if(a->r) a->r->p=a; up(a); b->p=0; return a;
    }else{
        b->l=mg(a,b->l); if(b->l) b->l->p=b; up(b); a->p=0; return b;
    }
}
pair<T*,T*> sp(T* t,int k){
    if(!t) return {0,0};
    if(sz(t->l)>=k){
        auto pr=sp(t->l,k);
        t->l=pr.second; if(t->l) t->l->p=t; up(t);
        if(pr.first) pr.first->p=0; return {pr.first,t};
    }else{
        int left=sz(t->l)+1;
        auto pr=sp(t->r,k-left);
        t->r=pr.first; if(t->r) t->r->p=t; up(t);
        if(pr.second) pr.second->p=0; return {t,pr.second};
    }
}
int rk(T* x){
    int r=sz(x->l)+1;
    while(x->p){ if(x==x->p->r) r+=sz(x->p->l)+1; x=x->p; }
    return r;
}
ll pref(T* x){
    ll a=sm(x->l);
    while(x->p){ if(x==x->p->r) a+=sm(x->p->l)+len(x->p); x=x->p; }
    return a;
}
pair<T*,ll> kth(T* t,ll k){
    while(t){
        ll ls=sm(t->l);
        if(k<=ls){ t=t->l; continue; }
        k-=ls;
        ll ln=len(t);
        if(k<=ln) return {t,k-1};
        k-=ln; t=t->r;
    }
    return {0,0};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(712367);

    int N; cin>>N;
    vector<pair<ll,ll>> v(N);
    ll mxLab=0, mxPos=0;
    for(int i=0;i<N;i++){
        cin>>v[i].first>>v[i].second;
        mxLab=max(mxLab,max(v[i].first,v[i].second));
    }
    int Q; cin>>Q;
    vector<pair<char,ll>> q(Q);
    for(int i=0;i<Q;i++){
        cin>>q[i].first>>q[i].second;
        if(q[i].first=='P') mxLab=max(mxLab,q[i].second);
        else mxPos=max(mxPos,q[i].second);
    }
    ll MAX=min(1000000000LL, max(mxLab, mxPos + (ll)N));

    T* rt=new T(1,MAX);
    map<ll,T*> mp; mp[1]=rt;

    auto findSeg = [&](ll x)->T*{
        auto it=mp.upper_bound(x); --it;
        return it->second;
    };

    auto cut = [&](ll x)->T*{
        T* t=findSeg(x);
        int i=rk(t);
        auto a=sp(rt,i-1);
        auto b=sp(a.second,1);
        ll L=t->L,R=t->R;
        mp.erase(L);
        T *u=0,*w=0;
        if(L<=x-1){ u=new T(L,x-1); mp[u->L]=u; }
        if(x+1<=R){ w=new T(x+1,R); mp[w->L]=w; }
        rt=mg(a.first, mg(u, mg(w, b.second)));
        T* s=new T(x,x); mp[s->L]=s;
        return s;
    };

    auto ins = [&](ll y,T* s){
        T* t=findSeg(y);
        int i=rk(t);
        auto a=sp(rt,i-1);
        auto b=sp(a.second,1);
        ll L=t->L,R=t->R;
        mp.erase(L);
        T *u=0,*v=0;
        if(L<=y-1){ u=new T(L,y-1); mp[u->L]=u; }
        v=new T(y,R); mp[v->L]=v;
        rt=mg(a.first, mg(u, mg(s, mg(v, b.second))));
    };

    for(auto [a,b]:v){
        T* s=cut(a);
        ins(b,s);
    }

    for(auto [c,x]:q){
        if(c=='P'){
            T* t=findSeg(x);
            cout<<pref(t)+(x-t->L)+1<<"\n";
        }else{
            auto pr=kth(rt,x);
            cout<<pr.first->L+pr.second<<"\n";
        }
    }
    return 0;
}
