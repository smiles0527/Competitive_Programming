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

    string s; cin >> s;
    int n = s.size();

    vector<int> z(n, 0), pi(n, 0);

    // Z-algorithm (standard z[0]=n, overridden to 0 on output)
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }

    // KMP prefix function
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }

    string out; out.reserve(14 * n);
    // z line: z(1)=0 by problem convention, then z[1..]
    out += '0';
    for (int i = 1; i < n; i++) { out += ' '; out += to_string(z[i]); }
    out += '\n';
    for (int i = 0; i < n; i++) { if (i) out += ' '; out += to_string(pi[i]); }
    out += '\n';
    cout << out;
    return 0;
}