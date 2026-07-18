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
const int B = 2000;
int g[B + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    g[1] = 0; g[2] = 0;
    for (int n = 3; n <= B; n++) {
        static bool seen[256];
        int hi = 0;
        for (int a = 1; a * 2 < n; a++) {        // a < n-a => unequal split
            int val = g[a] ^ g[n - a];
            if (val < 256) { seen[val] = true; if (val > hi) hi = val; }
        }
        int m = 0;
        while (m <= hi && seen[m]) m++;
        for (int a = 1; a * 2 < n; a++) {
            int val = g[a] ^ g[n - a];
            if (val < 256) seen[val] = false;
        }
        g[n] = m;
    }

    int t; cin >> t;
    string out;
    out.reserve(1 << 20);
    while (t--) {
        int n; cin >> n;
        bool second = (n <= B) ? (g[n] == 0) : false;   // past last zero: first wins
        out += (second ? "second" : "first");
        out += '\n';
    }
    cout << out;
    return 0;
}