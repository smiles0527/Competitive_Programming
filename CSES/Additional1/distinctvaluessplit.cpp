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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vi dp(n+1), pref(n+1);
    unordered_map<int, int> last;

    dp[0] = 1; pref[0] = 1;
    int left = 1;

    for(int i = 1; i <= n; i++){
        int x; cin >> x;

        if(last.count(x)) left = max(left, last[x] + 1);
        dp[i] = pref[i - 1];
        if(left >= 2) dp[i] = (dp[i] - pref[left - 2] + MOD) % MOD;

        pref[i] = (pref[i - 1] + dp[i]) % MOD;
        last[x] = i;
    }
    cout << dp[n] << '\n';
}