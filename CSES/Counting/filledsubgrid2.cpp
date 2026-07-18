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

    ll n, k;
    cin >> n >> k;

    vector<string> g(n);
    for(auto &str : g) cin >> str;

    vi ans(26, 0);
    vi h(n, 0);          // consecutive same-letter cells above, per column
    vii st(n);           // monotonic stack: {height, width}

    for(ll i = 0; i < n; i++){
        ll top = 0, S = 0;   // stack size; sum of min-heights over left boundaries in run
        for(ll j = 0; j < n; j++){
            h[j] = (i && g[i][j]==g[i-1][j]) ? h[j]+1 : 1;
            if(j==0 || g[i][j]!=g[i][j-1]){ top = 0; S = 0; }   // new letter run
            ll w = 1;
            while(top && st[top-1].f >= h[j]){ top--; S -= st[top].f*st[top].s; w += st[top].s; }
            st[top] = {h[j], w}; top++;
            S += h[j]*w;
            ans[g[i][j]-'A'] += S;
        }
    }

    for(ll c = 0; c < k; c++) cout << ans[c] << '\n';
    return 0;
}