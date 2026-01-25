#include <bits/stdc++.h>
using namespace std;

struct BIT{
    int n; vector<int> f;
    BIT(int n=0): n(n), f(n+1,0) {}
    void add(int i,int v){ for(; i<=n; i+=i&-i) f[i]+=v; }
    int sum(int i){ int s=0; for(; i>0; i-=i&-i) s+=f[i]; return s; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; 
    if(!(cin>>N)) return 0;
    vector<long long> a(N), b(N);
    for(int i=0;i<N;i++) cin>>a[i];
    for(int i=0;i<N;i++) cin>>b[i];

    unordered_map<long long,int> pos; pos.reserve(N*2);
    for(int i=0;i<N;i++) pos[a[i]]=i+1;

    vector<int> p(N);
    for(int i=0;i<N;i++) p[i]=pos[b[i]];

    int bestL=0,bestLen=1,curL=0,curLen=1;
    for(int i=1;i<N;i++){
        if(p[i]>p[i-1]) curLen++;
        else{
            if(curLen>bestLen){ bestLen=curLen; bestL=curL; }
            curL=i; curLen=1;
        }
    }
    if(curLen>bestLen){ bestLen=curLen; bestL=curL; }
    int bestR=bestL+bestLen-1;

    cout<<N-bestLen<<"\n";

    BIT bit(N);
    for(int i=1;i<=N;i++) bit.add(i,1);
    int front=0;

    for(int i=bestL-1;i>=0;i--){
        int idx = front + bit.sum(p[i]);
        cout<<"F "<<idx<<"\n";
        bit.add(p[i],-1);
        front++;
    }
    for(int i=bestR+1;i<N;i++){
        int idx = front + bit.sum(p[i]);
        cout<<"B "<<idx<<"\n";
        bit.add(p[i],-1);
    }
    return 0;
}
