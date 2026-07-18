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
    vector<int> sa(n), rnk(n);
    for (int i = 0; i < n; i++) { cin >> sa[i]; sa[i]--; }     // to 0-indexed
    for (int i = 0; i < n; i++) rnk[sa[i]] = i;

    auto nr = [&](int i) { return i < n ? rnk[i] : -1; };       // nrank, empty suffix = -1

    string res(n, 'a');
    int cur = 0;
    for (int i = 1; i < n; i++) {
        int a = sa[i-1], b = sa[i];
        if (nr(a + 1) >= nr(b + 1)) cur++;                      // tails not ordered -> must bump char
        if (cur > 25) { cout << -1 << '\n'; return 0; }
        res[b] = 'a' + cur;
    }
    cout << res << '\n';
    return 0;
}