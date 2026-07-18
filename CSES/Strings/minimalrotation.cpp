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
int leastRotation(const string& s) {
    int n = s.size();
    string t = s + s;
    vector<int> f(2 * n, -1);
    int k = 0;
    for (int j = 1; j < 2 * n; j++) {
        char sj = t[j];
        int i = f[j - k - 1];
        while (i != -1 && sj != t[k + i + 1]) {
            if (sj < t[k + i + 1]) k = j - i - 1;
            i = f[i];
        }
        if (sj != t[k + i + 1]) {
            if (sj < t[k + i + 1]) k = j;   // i == -1 here
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int k = leastRotation(s);
    int n = s.size();

    string out;
    out.reserve(n + 1);
    for (int i = 0; i < n; i++) out += s[(k + i) % n];
    out += '\n';
    cout << out;
    return 0;
}