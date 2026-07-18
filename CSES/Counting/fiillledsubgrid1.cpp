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
    for(auto &str : g) cin >> str;

    vi ans(26, 0);
    vector<int> prev(n, 0), cur(n, 0);   // rolling dp rows

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int d;
            if(i == 0 || j == 0){
                d = 1;
            } else if(g[i][j] == g[i-1][j] && g[i][j] == g[i][j-1] && g[i][j] == g[i-1][j-1]){
                d = 1 + min({prev[j], cur[j-1], prev[j-1]});
            } else {
                d = 1;
            }
            cur[j] = d;
            ans[g[i][j]-'A'] += d;
        }
        swap(prev, cur);
    }

    for(int c = 0; c < k; c++) cout << ans[c] << '\n';
    return 0;
}