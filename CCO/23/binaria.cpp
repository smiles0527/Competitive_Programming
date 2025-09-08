#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000003;

long long modpow(long long a,long long e){
    long long r=1%MOD;
    while(e){
        if(e&1) r=r*a%MOD;
        a=a*a%MOD;
        e>>=1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,K;
    if(!(cin>>N>>K)) return 0;
    int M=N-K+1;
    vector<int> s(M);
    for(int i=0;i<M;i++) cin>>s[i];

    long long F=0,S=0;
    for(int r=0;r<K;r++){
        long long pref=0,mn=0,mx=0;
        for(int j=r;j+1<M;j+=K){
            pref+=s[j+1]-s[j];
            if(pref<mn) mn=pref;
            if(pref>mx) mx=pref;
        }
        bool ok0=(mn>=0 && mx<=1);
        bool ok1=(mn>=-1 && mx<=0);
        if(!ok0 && !ok1){ cout<<0<<"\n"; return 0; }
        if(ok0 && ok1) F++;
        else if(ok1) S++;
    }

    long long need=s[0]-S;2
    if(need<0 || need>F){ cout<<0<<"\n"; return 0; }

    vector<long long> fact(K+1), invfact(K+1);
    fact[0]=1;
    for(int i=1;i<=K;i++) fact[i]=fact[i-1]*i%MOD;
    invfact[K]=modpow(fact[K],MOD-2);
    for(int i=K;i>=1;i--) invfact[i-1]=invfact[i]*i%MOD;

    auto C=[&](int n,int r)->long long{
        if(r<0||r>n) return 0;
        return fact[n]*invfact[r]%MOD*invfact[n-r]%MOD;
    };

    cout<<C((int)F,(int)need)<<"\n";
    return 0;
}
