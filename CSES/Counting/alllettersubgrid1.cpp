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

const ll INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    vector<string> g(n);
    for(auto &str : g) cin >> str;

    vector<char> gr((size_t)n*n);
    vi cnt(26, 0);
    for(ll i = 0; i < n; i++)
        for(ll j = 0; j < n; j++){
            char ch = g[i][j];
            gr[(size_t)i*n+j] = ch;
            cnt[ch-'A']++;
        }

    for(ll c = 0; c < k; c++) if(!cnt[c]){ cout << 0 << '\n'; return 0; }

    vi t((size_t)n*n, 0);   // accumulated max over letters = threshold
    vi pr(n), cu(n);        // rolling rows of S_c (row i+1, row i)

    for(ll c = 0; c < k; c++){
        char ch = 'A' + c;
        for(ll j = 0; j < n; j++) pr[j] = INF;     // row i+1 = n (none)
        for(ll i = n-1; i >= 0; i--){
            ll rightS = INF;                        // cur[i][j+1]
            size_t base = (size_t)i*n;
            for(ll j = n-1; j >= 0; j--){
                ll v;
                if(gr[base+j] == ch) v = 1;
                else {
                    ll diag = (j+1<n) ? pr[j+1] : INF;
                    ll m = min(pr[j], min(rightS, diag));
                    v = (m >= INF) ? INF : m+1;
                }
                cu[j] = v;
                rightS = v;
                if(v > t[base+j]) t[base+j] = v;
            }
            swap(pr, cu);
        }
    }

    ll ans = 0;
    for(ll i = 0; i < n; i++){
        size_t base = (size_t)i*n;
        for(ll j = 0; j < n; j++){
            ll ms = n - max(i, j);
            ll tt = t[base+j];
            if(tt <= ms) ans += (ms - tt + 1);
        }
    }
    cout << ans << '\n';
    return 0;
}