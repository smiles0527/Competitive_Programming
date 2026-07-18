#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string str; cin >> str;
    int n = str.size();
    if(n & 1){ cout << 0 << '\n'; return 0; }

    int H = n/2 + 1;
    vector<vi> C(H, vi(H, 0));
    for(int i=0;i<H;i++){ C[i][0]=1; for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD; }

    vector<vi> dp(n+1, vi(n+1, 0));
    auto get=[&](int i,int j)->ll{ if(i>j) return 1; return dp[i][j]; };

    for(int len=2; len<=n; len+=2){
        for(int i=0; i+len-1<n; i++){
            int j=i+len-1; ll cur=0;
            for(int k=i+1; k<=j; k++){
                if(str[k]!=str[i] || ((k-i)&1)==0) continue;
                int m1=(k-i+1)/2, m2=(j-k)/2;
                ll ways = get(i+1,k-1)*get(k+1,j)%MOD * C[m1+m2][m2]%MOD;
                cur=(cur+ways)%MOD;
            }
            dp[i][j]=cur;
        }
    }
    cout << get(0,n-1) << '\n';
    return 0;
}