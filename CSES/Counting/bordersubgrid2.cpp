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

    int n, k;
    cin >> n >> k;
    vector<string> g(n);
    for(auto &x : g) cin >> x;

    vector<int> R(n*n), D(n*n);              // right-run, down-run
    for(int i = n-1; i >= 0; i--)
        for(int j = n-1; j >= 0; j--){
            D[i*n+j] = (i==n-1 || g[i][j]!=g[i+1][j]) ? 1 : D[(i+1)*n+j]+1;
            R[i*n+j] = (j==n-1 || g[i][j]!=g[i][j+1]) ? 1 : R[i*n+j+1]+1;
        }

    vi ans(26, 0);
    vector<int> P(n+1);                       // prefix count of mono right-columns

    for(int i = 0; i < n; i++)
        for(int r = i; r < n; r++){
            int h = r - i + 1;
            P[0] = 0;
            for(int c = 0; c < n; c++) P[c+1] = P[c] + (D[i*n+c] >= h);   // col c mono over rows [i,r]
            for(int j = 0; j < n; j++){
                if(D[i*n+j] < h) continue;    // left col must be mono
                int e = j + min(R[i*n+j], R[r*n+j]) - 1;   // top & bottom edges mono on [j,e]
                if(e >= n) e = n-1;
                ans[g[i][j]-'A'] += P[e+1] - P[j];          // valid right cols in [j,e]
            }
        }

    for(int c = 0; c < k; c++) cout << ans[c] << '\n';
    return 0;
}