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

    int n; cin >> n;
    int m = n - 1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        if ((i & m) == i) ans ^= a;        // C(n-1,i) odd  <=>  i submask of n-1 (Lucas)
    }
    cout << ans << '\n';
    return 0;
}