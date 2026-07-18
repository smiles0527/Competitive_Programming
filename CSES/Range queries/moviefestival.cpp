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

const int T = 1000000;                  // max time
const int INF = T + 1;                  // sentinel free-time = unreachable
const int LOG = 18;                     // 2^18 > n_max chain length

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> jmp(T + 2, INF);        // min end among starts >= t
    for (int i = 0; i < n; i++){
        int a, b; cin >> a >> b;
        jmp[a] = min(jmp[a], b);
    }
    for (int t = T; t >= 1; t--) jmp[t] = min(jmp[t], jmp[t + 1]);
    jmp[INF] = INF;

    vector<vector<int>> up(LOG, vector<int>(T + 2));
    up[0] = jmp;
    for (int k = 1; k < LOG; k++)
        for (int t = 1; t <= T + 1; t++)
            up[k][t] = up[k-1][ up[k-1][t] ];

    while (q--){
        int A, B; cin >> A >> B;
        int cur = A, ans = 0;
        for (int k = LOG - 1; k >= 0; k--){
            int nx = up[k][cur];
            if (nx <= B){ ans += (1 << k); cur = nx; }
        }
        cout << ans << '\n';
    }
    return 0;
}