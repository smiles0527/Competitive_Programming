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
const int V = 1000000;
int cnt[V + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    for (int g = V; g >= 1; g--) {
        int c = 0;
        for (int m = g; m <= V; m += g) {
            c += cnt[m];
            if (c >= 2) break;
        }
        if (c >= 2) { cout << g << '\n'; return 0; }
    }

    cout << 1 << '\n';
    return 0;
}