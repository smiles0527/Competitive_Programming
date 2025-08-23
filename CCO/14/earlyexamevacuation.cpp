#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<int> f;
    BIT(int n): n(n), f(n+1,0) {}
    void add(int i,int v){ for(; i<=n; i+=i&-i) f[i]+=v; }
    int sumPrefix(int i){ int s=0; for(; i>0; i-=i&-i) s+=f[i]; return s; }
    int sumRange(int l,int r){ if(r<l) return 0; return sumPrefix(r)-sumPrefix(l-1); }
};

static inline void print_i128(__int128 x){
    if(x==0){ cout<<0; return; }
    if(x<0){ cout<<'-'; x=-x; }
    string s;
    while(x){ int d=int(x%10); s.push_back(char('0'+d)); x/=10; }
    reverse(s.begin(), s.end());
    cout<<s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; long long M,A,B;
    if(!(cin>>N>>M>>A>>B)) return 0;
    vector<int> r(M+1);
    vector<char> c(M+1);
    for(long long i=1;i<=M;i++){
        string t; cin>>t;
        if(isalpha(t.back())){ c[i]=t.back(); t.pop_back(); r[i]=stoi(t); }
        else{ r[i]=stoi(t); string t2; cin>>t2; c[i]=t2[0]; }
    }
    vector<char> occB(N+1,1), occE(N+1,1), occC(N+1,1), occD(N+1,1);
    BIT bit(N);
    for(int i=1;i<=N;i++) bit.add(i,2);
    vector<__int128> delta;
    delta.reserve(M);
    __int128 baseBack=0;
    for(long long i=1;i<=M;i++){
        int row=r[i];
        long long base=0;
        if(c[i]=='A') base += occB[row];
        if(c[i]=='F') base += occE[row];
        long long front = bit.sumPrefix(row);
        long long back = bit.sumRange(row,N);
        if(c[i]=='C' || c[i]=='D'){ front--; back--; }
        __int128 costF = (__int128)A * (base + front);
        __int128 costB = (__int128)A * (base + back);
        delta.push_back(costF - costB);
        baseBack += costB;
        if(c[i]=='B'){ if(occB[row]) occB[row]=0; }
        else if(c[i]=='E'){ if(occE[row]) occE[row]=0; }
        else if(c[i]=='C'){ if(occC[row]){ occC[row]=0; bit.add(row,-1); } }
        else if(c[i]=='D'){ if(occD[row]){ occD[row]=0; bit.add(row,-1); } }
    }
    sort(delta.begin(), delta.end());
    vector<__int128> pref(M+1,0);
    for(long long i=1;i<=M;i++) pref[i]=pref[i-1]+delta[i-1];
    __int128 ans = (__int128)LLONG_MAX<<1;
    for(long long k=0;k<=M;k++){
        __int128 t1 = (__int128)k*(k-1)/2;
        __int128 t2 = (__int128)(M-k)*(M-k-1)/2;
        __int128 total = baseBack + pref[k] + (__int128)B*(t1+t2);
        if(total<ans) ans=total;
    }
    print_i128(ans);
    return 0;
}
