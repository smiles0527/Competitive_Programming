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
    int n, x; cin >> n >> x;
    vector<int> h(n), s(n), k(n);
    for(auto& v : h) cin >> v;
    for(auto& v : s) cin >> v;
    for(auto& v : k) cin >> v;

    vector<int> dp(x + 1, 0);
    for(int i = 0; i < n; i++){
        int c = k[i];
        for(int b = 1; c > 0; b <<= 1){                  // binary-split the copy count
            int take = min(b, c); c -= take;
            int H = h[i]*take, S = s[i]*take;            // chunk = `take` copies at once
            for(int j = x; j >= H; j--) dp[j] = max(dp[j], dp[j-H] + S);   // 0/1 knapsack step
        }
    }
    cout << dp[x] << "\n";
}