#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> freq(n + 1, 0);
    for(int i = 0; i < n; i++){ int x; cin >> x; freq[x]++; }

    vector<ll> pw(n + 1); pw[0] = 1;
    for(int i = 1; i <= n; i++) pw[i] = pw[i-1] * 2 % MOD;

    vector<ll> m(n + 1, 0);
    for(int d = 1; d <= n; d++) for(int j = d; j <= n; j += d) m[d] += freq[j];   // multiples count

    vector<ll> ans(n + 1, 0);
    for(int d = n; d >= 1; d--){
        ll F = (pw[m[d]] - 1 + MOD) % MOD;                     // 2^{m_d} - 1
        for(int e = 2*d; e <= n; e += d) F = (F - ans[e] + MOD) % MOD;   // strip exact gcd = multiple of d
        ans[d] = F;
    }

    string out; out.reserve(n * 7);
    for(int d = 1; d <= n; d++){ out += to_string(ans[d]); out += ' '; }
    cout << out << "\n";
}