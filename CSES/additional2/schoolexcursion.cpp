#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;
const int MX = 100005;

int p[MX], sz[MX];
int find(int x){ while(p[x] != x) x = p[x] = p[p[x]]; return x; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; i++){ p[i] = i; sz[i] = 1; }
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a = find(a); b = find(b);
        if(a != b){ p[a] = b; sz[b] += sz[a]; }                 // union by attaching a under b
    }

    vector<int> cnt(n + 1, 0);
    for(int i = 1; i <= n; i++) if(find(i) == i) cnt[sz[i]]++;  // multiset of component sizes

    static bitset<MX> dp; dp[0] = 1;
    for(int s = 1; s <= n; s++) if(cnt[s]){                     // bounded knapsack, binary-split each count
        int c = cnt[s];
        for(int k = 1; c > 0; k <<= 1){
            int take = min(k, c); c -= take;
            dp |= dp << (s * take);                             // chunk of `take` components of size s
        }
    }

    string out(n, '0');
    for(int i = 1; i <= n; i++) if(dp[i]) out[i-1] = '1';       // one-indexed
    cout << out << "\n";
}