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

    vector<ll> D(n + 1);                 // D[i] = distinct subseqs of s[1..i] incl. empty
    D[0] = 1;
    int last[26]; memset(last, 0, sizeof(last));   // last[c] = last 1-indexed pos of c, 0 = none

    for (int i = 1; i <= n; i++) {
        int c = s[i-1] - 'a';
        D[i] = 2 * D[i-1] % MOD;
        if (last[c]) D[i] = (D[i] - D[last[c] - 1] + MOD) % MOD;   // remove dupes from prior occurrence
        last[c] = i;
    }

    cout << (D[n] - 1 + MOD) % MOD << '\n';   // drop empty subsequence
    return 0;
}