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

    string t;
    t.reserve(2 * n + 3);
    t += '^';
    for (char ch : s) { t += '#'; t += ch; }
    t += '#';
    t += '$';

    int m = t.size();
    vector<int> p(m, 0);
    int c = 0, r = 0;
    for (int i = 1; i < m - 1; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
        if (i + p[i] > r) { c = i; r = i + p[i]; }
    }

    vector<int> ans(n, 0);
    for (int i = 1; i < m - 1; i++) {
        if (p[i] == 0) continue;
        int len = p[i];                 // palindrome length in original
        int e = (i + p[i]) / 2 - 1;     // ending index in s
        ans[e] = max(ans[e], len);
    }
    for (int j = n - 1; j >= 1; j--)
        if (ans[j] - 2 > ans[j - 1]) ans[j - 1] = ans[j] - 2;   // peel co-centered

    string out;
    out.reserve(1 << 21);
    for (int j = 0; j < n; j++) { out += to_string(ans[j]); out += (j == n - 1 ? '\n' : ' '); }
    cout << out;
    return 0;
}