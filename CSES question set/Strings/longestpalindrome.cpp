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
    int c = 0, r = 0, bl = 0, bc = 0;   // best len, best center
    for (int i = 1; i < m - 1; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
        if (i + p[i] > r) { c = i; r = i + p[i]; }
        if (p[i] > bl) { bl = p[i]; bc = i; }
    }

    cout << s.substr((bc - bl) / 2, bl) << '\n';
    return 0;
}