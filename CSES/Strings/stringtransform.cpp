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

    string L; cin >> L;
    int N = L.size();                       // = n+1, contains exactly one '#'

    int cnt[128] = {0}, start[128] = {0};
    for (char c : L) cnt[(int)c]++;
    int sum = 0;                            // '#'(35) < 'a'..'z'; iterate ascending ascii
    for (int c = 0; c < 128; c++) { start[c] = sum; sum += cnt[c]; }

    int occ[128] = {0};
    vector<int> lf(N);
    for (int i = 0; i < N; i++) {           // LF(i) = start[L_i] + rank of L_i so far
        int c = L[i];
        lf[i] = start[c] + occ[c]++;
    }

    string r(N, 0);                         // r = rev(S) + '#'
    int p = 0;                              // row 0 has F='#', i.e. "#S"
    for (int k = 0; k < N; k++) { r[k] = L[p]; p = lf[p]; }

    string out(N - 1, 0);                   // drop trailing '#', reverse
    for (int i = 0; i < N - 1; i++) out[i] = r[N - 2 - i];
    out += '\n';
    cout << out;
    return 0;
}