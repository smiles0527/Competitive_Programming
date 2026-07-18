#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back
#define fs first
#define sn second
#define FR(i,n) for(int i=0;i<(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define FORR(i,a,b) for(int i=(a);i>=(b);--i)

int T,n,m,w,h,dep;
pii ip1,ip2,p1,p2;
list<pii> ans;
bool vis[55][55];

int dst(pii a, pii b){
    return abs(a.fs-b.fs)+abs(a.sn-b.sn);
}

bool good(){
    int mn=min(n,m), mx=max(n,m);
    int q1=(ip1.fs+ip1.sn)&1, q2=(ip2.fs+ip2.sn)&1;

    if((n*m)&1){
        if(q1||q2) return 0;
        if(mn==1&&dst(ip1,ip2)!=mx-1) return 0;
        return 1;
    }

    if(q1==q2) return 0;
    if(mn==1) return dst(ip1,ip2)==mx-1;

    if(mn==2){
        if(n>=m) return ip1.fs!=ip2.fs||ip1.fs==0||ip1.fs==n-1;
        return ip1.sn!=ip2.sn||ip1.sn==0||ip1.sn==m-1;
    }

    if(mn==3){
        if(n>=m){
            if(q1){
                if(ip1.sn==1&&ip1.fs<ip2.fs) return 0;
                if(ip1.sn!=1&&ip1.fs<ip2.fs-1) return 0;
            }
            if(q2){
                if(ip2.sn==1&&ip2.fs<ip1.fs) return 0;
                if(ip2.sn!=1&&ip2.fs<ip1.fs-1) return 0;
            }
        }else{
            if(q1){
                if(ip1.fs==1&&ip1.sn<ip2.sn) return 0;
                if(ip1.fs!=1&&ip1.sn<ip2.sn-1) return 0;
            }
            if(q2){
                if(ip2.fs==1&&ip2.sn<ip1.sn) return 0;
                if(ip2.fs!=1&&ip2.sn<ip1.sn-1) return 0;
            }
        }
    }

    return 1;
}

bool dfs(int x,int y){
    if(x<0||x>=w||y<0||y>=h||vis[x][y]) return 0;

    ++dep;
    vis[x][y]=1;

    bool ok=(x==p1.fs&&y==p1.sn&&dep==w*h)||dfs(x-1,y)||dfs(x+1,y)||dfs(x,y-1)||dfs(x,y+1);

    if(ok) ans.pb({x,y});

    vis[x][y]=0;
    --dep;

    return ok;
}

#define rotPt(p,y) p={y-p.sn-1,p.fs}

void rot(){
    rotPt(ip1,m);
    rotPt(ip2,m);
    rotPt(p1,h);
    rotPt(p2,h);

    for(auto &p:ans) rotPt(p,h);

    swap(n,m);
    swap(w,h);
}

void procPre(){
    if(ip2<ip1) return;

    int b=ip2.fs-ip1.fs;

    p1.fs=ip1.fs&1;
    p2.fs=p1.fs+min(b,b%2+2);
    w=p2.fs+(n-ip2.fs-1)%2+1;

    while((w<n)&&(w<4||h==1)){
        p1.fs+=2*(p1.fs<ip1.fs);
        p2.fs+=2*(p2.fs<ip2.fs);
        w+=2;
    }
}

bool addCol(int x){
    if(x==0||x==w){
        for(auto &[i,j]:ans) if(i>=x) i+=2;

        w+=2;

        int a,b,c;

        if(x==0) a=2,b=1,c=0;
        else a=w-3,b=w-2,c=w-1;

        auto pr=ans.begin();

        for(auto it=next(ans.begin());it!=ans.end();pr=it,++it){
            auto [x1,y1]=*pr;
            auto [x2,y2]=*it;

            if(x1==a&&x2==a){
                if(y1<y2){
                    FORR(i,y1,0) ans.insert(it,{b,i});
                    FR(i,h) ans.insert(it,{c,i});
                    FORR(i,h-1,y2) ans.insert(it,{b,i});
                }else{
                    FOR(i,y1,h) ans.insert(it,{b,i});
                    FORR(i,h-1,0) ans.insert(it,{c,i});
                    FR(i,y2+1) ans.insert(it,{b,i});
                }

                return 1;
            }
        }

        return 0;
    }

    vector<pair<list<pii>::iterator,list<pii>::iterator>> v;
    bool z=0;

    auto pr=ans.begin();

    for(auto it=next(ans.begin());it!=ans.end();pr=it,++it){
        auto [x1,y1]=*pr;
        auto [x2,y2]=*it;

        if((x1==x&&x2==x-1)||(x1==x-1&&x2==x)){
            v.pb({pr,it});
            if(!y1) z=1;
        }
    }

    if(!z) return 0;

    for(auto &[i,j]:ans) if(i>=x) i+=2;

    w+=2;

    sort(v.begin(),v.end(),[](auto a,auto b){
        return a.fs->sn<b.fs->sn;
    });

    FR(i,(int)v.size()){
        auto [i1,i2]=v[i];

        int nxt=i+1==(int)v.size()?h:v[i+1].fs->sn;

        auto [x1,y1]=*i1;
        auto [x2,y2]=*i2;

        if(x1<x) ++x1,--x2;
        else --x1,++x2;

        FOR(j,y1,nxt) ans.insert(i2,{x1,j});
        FORR(j,nxt-1,y1) ans.insert(i2,{x2,j});
    }

    return 1;
}

void procMain(){
    if(ip2<ip1) return;

    while(p1.fs<ip1.fs) addCol(0),p1.fs+=2,p2.fs+=2;
    while(p2.fs<ip2.fs) addCol(p1.fs+1)||addCol(p1.fs+2),p2.fs+=2;
    while(w<n) addCol(w);
}

void solve(){
    int a,b,c,d;
    cin>>n>>m>>a>>b>>c>>d;

    ip1=p1={--a,--b};
    ip2=p2={--c,--d};

    w=n;
    h=m;
    dep=0;

    memset(vis,0,sizeof vis);

    if(!good()) return;

    FR(i,4) procPre(),rot();

    if(dfs(p2.fs,p2.sn)) FR(i,4) procMain(),rot();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>T;

    while(T--){
        solve();

        if(ans.empty()){
            cout<<"NO\n";
        }else{
            cout<<"YES\n";

            auto it=ans.begin(), pr=it++;

            FR(i,n*m-1){
                int x=it->fs-pr->fs;
                int y=it->sn-pr->sn;

                ++it;
                ++pr;

                cout<<"LU DR"[2+x+2*y];
            }

            cout<<'\n';
        }

        ans.clear();
    }
}