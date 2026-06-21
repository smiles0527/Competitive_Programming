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

    string s;
    cin >> s;
    int n = s.size();

    vector<int> fail(n, 0);
    for (int i = 1, len = 0; i < n; ) {
        if (s[i] == s[len]) {
            fail[i++] = ++len;
        } else if (len > 0) {
            len = fail[len - 1];
        } else {
            fail[i++] = 0;
        }
    }

    vector<int> borders;
    for (int b = fail[n - 1]; b > 0; b = fail[b - 1])
        borders.push_back(b);

    for (int i = borders.size() - 1; i >= 0; i--)
        cout << borders[i] << " ";
    cout << "\n";

    return 0;
}