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

int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<int> adj(n, 0);
    for(int i = 0; i < m; i++){ int a, b; cin >> a >> b; --a; --b; if(a != b){ adj[a] |= 1 << b; adj[b] |= 1 << a; } }

    int F = 1 << n;
    vector<char> ind(F, 0); ind[0] = 1;
    for(int mask = 1; mask < F; mask++){
        int low = __builtin_ctz(mask);
        ind[mask] = ind[mask ^ (1 << low)] && !(adj[low] & mask);   // drop low, check no neighbor inside
    }

    vector<int> dp(F, INT_MAX), ch(F, 0);
    dp[0] = 0;
    for(int mask = 1; mask < F; mask++){
        int low = __builtin_ctz(mask), rest = mask ^ (1 << low);
        for(int t = rest; ; t = (t - 1) & rest){
            int sub = t | (1 << low);                                // color class containing low
            if(ind[sub] && dp[mask ^ sub] != INT_MAX && dp[mask ^ sub] + 1 < dp[mask]){ dp[mask] = dp[mask ^ sub] + 1; ch[mask] = sub; }
            if(t == 0) break;
        }
    }

    vector<int> col(n);
    int mask = F - 1, c = 0;
    while(mask){ ++c; int sub = ch[mask]; for(int i = 0; i < n; i++) if(sub >> i & 1) col[i] = c; mask ^= sub; }

    cout << dp[F - 1] << "\n";
    for(int i = 0; i < n; i++) cout << col[i] << " \n"[i + 1 == n];
}