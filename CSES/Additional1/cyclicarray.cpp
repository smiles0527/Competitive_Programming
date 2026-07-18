#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int LOG = 18;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n; ll k; cin >> n >> k;
    vector<ll> a(2*n);
    for(int i = 0; i < n; i++){ cin >> a[i]; a[i+n] = a[i]; }
 
    int M = 2*n;
    vector<ll> pre(M+1, 0);
    for(int i = 0; i < M; i++) pre[i+1] = pre[i] + a[i];
 
    // jump[i] = start of next segment when greedily packing from i
    vector<int> jump(M+1, M);
    int r = 0;
    for(int i = 0; i < M; i++){
        if(r < i) r = i;
        while(r < M && pre[r+1] - pre[i] <= k) r++;   // extend while sum ≤ k
        jump[i] = r;                                   // segment = [i, r-1]
    }
    jump[M] = M;
 
    vector<vector<int>> up(LOG, vector<int>(M+1));
    up[0] = jump;
    for(int t = 1; t < LOG; t++)
        for(int i = 0; i <= M; i++)
            up[t][i] = up[t-1][up[t-1][i]];
 
    ll ans = LLONG_MAX;
    for(int s = 0; s < n; s++){
        int target = s + n, pos = s; ll cnt = 0;
        for(int t = LOG-1; t >= 0; t--)
            if(up[t][pos] < target){ pos = up[t][pos]; cnt += (1LL<<t); }
        cnt++;                                          // final segment covering target
        ans = min(ans, cnt);
    }
    cout << ans << '\n';
}