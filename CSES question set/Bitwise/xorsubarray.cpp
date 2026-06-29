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
const int MOD = 1e9+7;

const int B = 30;
const int MX = 200005 * (B + 1);
int ch[MX][2], cnt;

void insert(int x) {
    int u = 0;
    for (int b = B; b >= 0; b--) {
        int d = (x >> b) & 1;
        if (!ch[u][d]) { ch[u][d] = ++cnt; ch[cnt][0] = ch[cnt][1] = 0; }
        u = ch[u][d];
    }
}

int query(int x) {                          // max x ^ stored
    int u = 0, res = 0;
    for (int b = B; b >= 0; b--) {
        int d = (x >> b) & 1;
        if (ch[u][d ^ 1]) { res |= (1 << b); u = ch[u][d ^ 1]; }
        else u = ch[u][d];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    cnt = 0; ch[0][0] = ch[0][1] = 0;

    int pref = 0, ans = 0;
    insert(0);                              // P_0
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        pref ^= x;
        ans = max(ans, query(pref));
        insert(pref);
    }
    cout << ans << '\n';
    return 0;
}