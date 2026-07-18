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

    string s, p;
    cin >> s >> p;
    int n = s.size(), m = p.size();

    vector<int> fail(m, 0);
    for (int i = 1, len = 0; i < m; ) {
        if (p[i] == p[len]) {
            fail[i++] = ++len;
        } else if (len > 0) {
            len = fail[len - 1];
        } else {
            fail[i++] = 0;
        }
    }

    int count = 0;
    for (int i = 0, len = 0; i < n; i++) {
        while (len > 0 && s[i] != p[len]) len = fail[len - 1];
        if (s[i] == p[len]) len++;
        if (len == m) {
            count++;
            len = fail[len - 1];
        }
    }

    cout << count << "\n";
    return 0;
}