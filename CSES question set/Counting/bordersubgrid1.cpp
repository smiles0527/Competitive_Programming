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

static int bitarr[3005], remHead[3005], remNext[3005], RA[3005], LB[3005], vG[3005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<string> g(n);
    for(auto &x : g) cin >> x;
    
    // vector<int> rcm((size_t)n*n);   // right-run, column-major
    // vector<int> drm((size_t)n*n);   // down-run,  row-major
    // for(int i = n-1; i >= 0; i--)
    //     for(int j = n-1; j >= 0; j--){
    //         drm[(size_t)i*n+j] = (i==n-1 || g[i][j]!=g[i+1][j]) ? 1 : drm[(size_t)(i+1)*n+j]+1;
    //         rcm[(size_t)j*n+i] = (j==n-1 || g[i][j]!=g[i][j+1]) ? 1 : rcm[(size_t)(j+1)*n+i]+1;
    //     }
    // vector<int> prev(n,0), cur(n,0);
    // for(int i = n-1; i >= 0; i--){
    //     for(int j = n-1; j >= 0; j--){
    //         int ms;
    //         if(i==n-1 || j==n-1) ms = 1;
    //         else if(g[i][j]==g[i+1][j] && g[i][j]==g[i][j+1] && g[i][j]==g[i+1][j+1])
    //             ms = 1 + min({prev[j], cur[j+1], prev[j+1]});
    //         else ms = 1;
    //         cur[j] = ms;
    //         int rr = rcm[(size_t)j*n+i], dd = drm[(size_t)i*n+j];
    //         int m = rr < dd ? rr : dd;
    //         ll c = ms;
    //         const int* rcol = &rcm[(size_t)j*n];
    //         const int* drow = &drm[(size_t)i*n];
    //         for(int sd = ms+1; sd <= m; sd++)
    //             if(rcol[i+sd-1] >= sd && drow[j+sd-1] >= sd) c++;
    //         ans[g[i][j]-'A'] += c;
    //     }
    //     swap(prev, cur);
    // }

    // four directional runs (big buffers kept int for memory/speed)
    vector<int> R(n*n), D(n*n), HL(n*n), VU(n*n), A(n*n), B(n*n);
    for(int i = n-1; i >= 0; i--)
        for(int j = n-1; j >= 0; j--){
            D[i*n+j] = (i==n-1 || g[i][j]!=g[i+1][j]) ? 1 : D[(i+1)*n+j]+1;
            R[i*n+j] = (j==n-1 || g[i][j]!=g[i][j+1]) ? 1 : R[i*n+j+1]+1;
        }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            VU[i*n+j] = (i==0 || g[i][j]!=g[i-1][j]) ? 1 : VU[(i-1)*n+j]+1;
            HL[i*n+j] = (j==0 || g[i][j]!=g[i][j-1]) ? 1 : HL[i*n+j-1]+1;
            A[i*n+j] = min(R[i*n+j], D[i*n+j]);   // TL bound: s <= A
            B[i*n+j] = min(HL[i*n+j], VU[i*n+j]); // BR bound: s <= B
        }

    vi ans(26, 0);

    auto run = [&](int si, int sj){          // one down-right diagonal
        int len = 0;
        for(int i=si, j=sj; i<n && j<n; i++, j++){
            int p = len, a = A[i*n+j], b = B[i*n+j];
            RA[p] = p + a - 1;               // TL p reaches q <= RA[p]
            LB[p] = p - b + 1;               // BR p needs p' >= LB[p]
            vG[p] = g[i][j]-'A';
            len++;
        }
        for(int p=0; p<=len; p++) bitarr[p] = 0;
        for(int p=0; p<len; p++) remHead[p] = -1;
        ll alive = 0;
        for(int q=0; q<len; q++){
            if(q) for(int p=remHead[q-1]; p!=-1; p=remNext[p]){   // p died: RA[p] < q
                alive--; for(int x=p+1; x<=len; x+=x&-x) bitarr[x]--;
            }
            alive++; for(int x=q+1; x<=len; x+=x&-x) bitarr[x]++;  // insert q (s=1)
            int ra = RA[q]; remNext[q] = remHead[ra]; remHead[ra] = q;
            int lo = LB[q];
            ll cnt;
            if(lo <= 0) cnt = alive;                              // whole alive set qualifies
            else { ll sm=0; for(int x=lo; x>0; x-=x&-x) sm += bitarr[x]; cnt = alive - sm; }
            ans[vG[q]] += cnt;                                    // border letter = g[q]
        }
    };

    for(int j=0; j<n; j++) run(0, j);
    for(int i=1; i<n; i++) run(i, 0);

    for(int c=0; c<k; c++) cout << ans[c] << '\n';
    return 0;
}