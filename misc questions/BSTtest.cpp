#include <bits/stdc++.h>
using namespace std;

struct BIT{
    int n; vector<int> f;
    BIT(int n=0): n(n), f(n+1,0) {}
    void add(int i,int v){ for(; i<=n; i+=i&-i) f[i]+=v; }
    int sum(int i){ int s=0; for(; i>0; i-=i&-i) s+=f[i]; return s; }
    int kth(int k){
        int idx=0, bit=1;
        while((bit<<1)<=n) bit<<=1;
        for(int j=bit;j;j>>=1){
            int nxt=idx+j;
            if(nxt<=n && f[nxt]<k){ idx=nxt; k-=f[nxt]; }
        }
        return idx+1;
    }
    int freq(int i){ return sum(i)-sum(i-1); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M;
    if(!(cin>>N>>M)) return 0;
    const int LIM=1000000;
    BIT ft(LIM);

    for(int i=0;i<N;i++){ int x; cin>>x; if(1<=x && x<=LIM) ft.add(x,1); }

    long long last=0;
    for(int i=0;i<M;i++){
        char c; long long v; 
        cin>>c>>v;
        long long x = v ^ last;

        if(c=='I'){
            if(1<=x && x<=LIM) ft.add((int)x,1);
        }else if(c=='R'){
            if(1<=x && x<=LIM && ft.freq((int)x)>0) ft.add((int)x,-1);
        }else if(c=='S'){
            int k=(int)x;
            int val=ft.kth(k);
            cout<<val<<"\n";
            last=val;
        }else if(c=='L'){
            if(!(1<=x && x<=LIM) || ft.freq((int)x)==0){
                cout<<-1<<"\n";
                last=-1;
            }else{
                int idx=ft.sum((int)x-1)+1;
                cout<<idx<<"\n";
                last=idx;
            }
        }
    }

    bool first=true;
    for(int v=1; v<=LIM; v++){
        int cnt=ft.freq(v);
        while(cnt--){
            if(!first) cout<<' ';
            cout<<v;
            first=false;
        }
    }
    cout<<"\n";
    return 0;
}
