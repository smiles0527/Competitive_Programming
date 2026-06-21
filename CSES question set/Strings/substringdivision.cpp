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

const int MX = 200005;                  // up to 2n states
int nxt[MX][26], link_[MX], len_[MX];
int sz, last;

void sa_init() {
    sz = 0; last = 0;
    memset(nxt[0], -1, sizeof(nxt[0]));
    link_[0] = -1; len_[0] = 0; sz++;
}

void sa_extend(int c) {
    int cur = sz++;
    memset(nxt[cur], -1, sizeof(nxt[cur]));
    len_[cur] = len_[last] + 1; link_[cur] = -1;
    int p = last;
    while (p != -1 && nxt[p][c] == -1) { nxt[p][c] = cur; p = link_[p]; }
    if (p == -1) link_[cur] = 0;
    else {
        int q = nxt[p][c];
        if (len_[p] + 1 == len_[q]) link_[cur] = q;
        else {
            int cl = sz++;
            len_[cl] = len_[p] + 1;
            memcpy(nxt[cl], nxt[q], sizeof(nxt[q]));
            link_[cl] = link_[q];
            while (p != -1 && nxt[p][c] == q) { nxt[p][c] = cl; p = link_[p]; }
            link_[q] = link_[cur] = cl;
        }
    }
    last = cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int n = s.size();

    sa_init();
    for (char ch : s) sa_extend(ch - 'a');

    vector<ll> d(n + 2, 0);             // difference array over lengths
    for (int u = 1; u < sz; u++) {
        d[len_[link_[u]] + 1]++;        // range (len(link), len(u)] gets +1 each length
        d[len_[u] + 1]--;
    }

    string out; out.reserve(7 * n);
    ll run = 0;
    for (int L = 1; L <= n; L++) {
        run += d[L];
        if (L > 1) out += ' ';
        out += to_string(run);
    }
    out += '\n';
    cout << out;
    return 0;
}