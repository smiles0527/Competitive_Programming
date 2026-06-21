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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; cin >> n >> k;
    vector<int> p(k);
    for (auto& v : p) cin >> v;

    vector<char> dp(n + 1, 'L');   // dp[0] = L
    for (int s = 1; s <= n; s++) {
        char res = 'L';
        for (int i = 0; i < k; i++) {
            if (p[i] <= s && dp[s - p[i]] == 'L') { res = 'W'; break; }
        }
        dp[s] = res;
    }

    string out(n, ' ');
    for (int s = 1; s <= n; s++) out[s-1] = dp[s];
    cout << out << '\n';
    return 0;
}