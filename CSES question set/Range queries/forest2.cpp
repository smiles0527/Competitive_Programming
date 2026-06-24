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

int n, q;
int bit[1001][1001];
int cur[1001][1001];                    // current cell state (1 = tree)

void upd(int y, int x, int v){
    for (int i = y; i <= n; i += i & -i)
        for (int j = x; j <= n; j += j & -j)
            bit[i][j] += v;
}
int pre(int y, int x){                  // sum over [1..y][1..x]
    int r = 0;
    for (int i = y; i > 0; i -= i & -i)
        for (int j = x; j > 0; j -= j & -j)
            r += bit[i][j];
    return r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++){
        string row; cin >> row;
        for (int j = 1; j <= n; j++){
            if (row[j-1] == '*'){ cur[i][j] = 1; upd(i, j, 1); }
        }
    }

    while (q--){
        int op; cin >> op;
        if (op == 1){
            int y, x; cin >> y >> x;
            int d = cur[y][x] ? -1 : 1;         // toggle
            cur[y][x] ^= 1;
            upd(y, x, d);
        } else {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << pre(y2, x2) - pre(y1-1, x2) - pre(y2, x1-1) + pre(y1-1, x1-1) << '\n';
        }
    }
    return 0;
}