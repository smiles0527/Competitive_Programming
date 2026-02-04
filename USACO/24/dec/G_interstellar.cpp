#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

struct bit{
    int n;
    vector<int> f;
    bit(){}
    bit(int n_){ init(n_); }
    void init(int n_){ n=n_+2; f.assign(n+1,0); }
    void add(int i,int v){
        i++;
        if(v>=MOD) v-=MOD;
        for(int x=i;x<=n;x+=x&-x){
            int t=f[x]+v;
            if(t>=MOD) t-=MOD;
            f[x]=t;
        }
    }
    int sum(int i){
        if(i<0) return 0;
        i++;
        long long r=0;
        for(int x=i;x>0;x-=x&-x) r+=f[x];
        return (int)(r%MOD);
    }
    int sum(int l,int r){
        if(r<l) return 0;
        int a=sum(r), b=sum(l-1);
        int t=a-b;
        if(t<0) t+=MOD;
        return t;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    string s; cin >> s;
    string t=" "+s;

    vector<int> nb(n+1, n+1);
    int nxt=n+1;
    for(int i=n;i>=1;i--){
        if(t[i]=='B') nxt=i;
        nb[i-1]=nxt;
    }
    nb[n]=n+1;

    vector<int> dp(n+1,0);
    dp[0]=1;

    bit b[2];
    b[0].init(n+1);
    b[1].init(n+1);

    vector<vector<pair<int,int>>> rm(n+2);

    auto lim = [&](int j)->int{
        int x=nb[j];
        if(x==n+1) return n;
        long long v=2LL*x-j-1;
        if(v<0) return -1;
        if(v>n) v=n;
        return (int)v;
    };

    auto ins = [&](int j,int v){
        b[j&1].add(j,v);
        int L=lim(j)+1;
        if(1<=L && L<=n) rm[L].push_back({j,v});
    };

    ins(0, dp[0]);

    int lr=0;
    for(int i=1;i<=n;i++){
        for(auto &p: rm[i]){
            int j=p.first, v=p.second;
            int w=MOD-v;
            b[j&1].add(j,w);
        }

        if(t[i]=='R') lr=i;

        int L=2*lr-i;
        if(L<0) L=0;

        int seg=0;
        if(t[i]!='R') seg=b[i&1].sum(L, i-1);

        int w=(t[i]=='X')? dp[i-1] : 0;
        int v=w+seg;
        if(v>=MOD) v-=MOD;
        dp[i]=v;

        ins(i, dp[i]);
    }

    cout << dp[n] << "\n";
    return 0;
}
