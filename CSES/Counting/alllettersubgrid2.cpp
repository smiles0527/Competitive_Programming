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
const int IINF = 1 << 29;                  

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

    // vi t((size_t)n*n, 0);   // accumulated max over letters = threshold
    // vi pr(n), cu(n);        // rolling rows of S_c (row i+1, row i)
    //
    // for(ll c = 0; c < k; c++){
    //     char ch = 'A' + c;
    //     for(ll j = 0; j < n; j++) pr[j] = INF;     // row i+1 = n (none)
    //     for(ll i = n-1; i >= 0; i--){
    //         ll rightS = INF;                        // cur[i][j+1]
    //         size_t base = (size_t)i*n;
    //         for(ll j = n-1; j >= 0; j--){
    //             ll v;
    //             if(gr[base+j] == ch) v = 1;
    //             else {
    //                 ll diag = (j+1<n) ? pr[j+1] : INF;
    //                 ll m = min(pr[j], min(rightS, diag));
    //                 v = (m >= INF) ? INF : m+1;
    //             }
    //             cu[j] = v;
    //             rightS = v;
    //             if(v > t[base+j]) t[base+j] = v;
    //         }
    //         swap(pr, cu);
    //     }
    // }
    //
    // ll ans = 0;
    // for(ll i = 0; i < n; i++){
    //     size_t base = (size_t)i*n;
    //     for(ll j = 0; j < n; j++){
    //         ll ms = n - max(i, j);
    //         ll tt = t[base+j];
    //         if(tt <= ms) ans += (ms - tt + 1);
    //     }
    // }

    int N = n, K = k;
    vector<int> prv((size_t)N*K), cur((size_t)N*K);   // layout: idx = j*K + c
    for(auto &x : prv) x = IINF;                       // row below grid = none

    ll ans = 0;
    for(int i = N-1; i >= 0; i--){
        const char* row = &gr[(size_t)i*N];
        for(int j = N-1; j >= 0; j--){
            int cc = row[j] - 'A';
            size_t cb = (size_t)j*K, cbr = (size_t)(j+1)*K;
            bool hr = (j+1 < N);
            int tmax = 0;
            for(int c = 0; c < K; c++){
                int sv;
                if(c == cc) sv = 1;
                else {
                    int m = prv[cb + c];               // below
                    if(hr){
                        int r = cur[cbr + c], d = prv[cbr + c];   // right, diag
                        if(r < m) m = r;
                        if(d < m) m = d;
                    }
                    sv = (m >= IINF) ? IINF : m + 1;
                }
                cur[cb + c] = sv;
                if(sv > tmax) tmax = sv;
            }
            int ms = N - (i > j ? i : j);             // largest square side at (i,j)
            if(tmax <= ms) ans += (ms - tmax + 1);
        }
        swap(prv, cur);
    }

    cout << ans << '\n';
    return 0;
}