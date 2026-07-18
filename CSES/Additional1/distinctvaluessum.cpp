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
    unordered_map<int, int> last;
    ll ans = 0;

    for(int i = 1; i <= n; i++){
        int x; cin >> x;

        int prev = last[x];
        ans += 1LL * (i - prev) * (n - i + 1);
        last[x] = i;
    }
    cout << ans << '\n';
}