    #include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<char> g((size_t)n * n);
    for (int i = 0; i < n; i++) {
        string row; cin >> row;
        memcpy(&g[(size_t)i * n], row.data(), n);
    }

    vector<signed char> seen((size_t)n * n, -1);   // seen[a*n+b] = letter that owns pair (a,b)
    vector<int> cs; cs.reserve(n);

    for (int c = 0; c < k; c++) {
        char ch = 'A' + c;
        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            size_t base = (size_t)i * n;
            cs.clear();
            for (int j = 0; j < n; j++) if (g[base + j] == ch) cs.pb(j);
            int sz = cs.size();
            for (int a = 0; a < sz && !found; a++) {
                size_t ra = (size_t)cs[a] * n;
                for (int b = a + 1; b < sz; b++) {
                    size_t idx = ra + cs[b];
                    if (seen[idx] == c) { found = true; break; }   // pair repeats in 2 rows
                    seen[idx] = c;
                }
            }
        }
        cout << (found ? "YES" : "NO") << "\n";
    }
}