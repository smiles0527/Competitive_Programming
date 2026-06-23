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
const ll MOD = 1e9 + 7;

ll power(ll a, ll b) {
    a %= MOD; ll r = 1;
    while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int n = s.size();
    vector<ll> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;

    ll cnt[26] = {0};
    for (char ch : s) cnt[ch - 'a']++;

    ll ans = fact[n];
    for (int i = 0; i < 26; i++)
        if (cnt[i]) ans = ans * power(fact[cnt[i]], MOD - 2) % MOD;

    cout << ans << '\n';
    return 0;
}