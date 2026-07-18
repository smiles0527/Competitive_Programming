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
int nxt[MX][26], link_[MX], len_[MX], cnt[MX], pos[MX];
int sz, last;

void sa_init() {
    sz = 0; last = 0;
    memset(nxt[0], -1, sizeof(nxt[0]));
    link_[0] = -1; len_[0] = 0; cnt[0] = 0; pos[0] = 0; sz++;
}

void sa_extend(int c, int i) {
    int cur = sz++;
    memset(nxt[cur], -1, sizeof(nxt[cur]));
    len_[cur] = len_[last] + 1; link_[cur] = -1;
    cnt[cur] = 1; pos[cur] = i;                  // primary state: one endpos, ends at i (0-indexed)
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
            cnt[cl] = 0; pos[cl] = pos[q];       // clone: no own endpos
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
    for (int i = 0; i < n; i++) sa_extend(s[i] - 'a', i);

    // counting sort states by len, then propagate cnt up the link tree
    vector<int> ord(sz), bk(n + 1, 0);
    for (int u = 0; u < sz; u++) bk[len_[u]]++;
    for (int i = 1; i <= n; i++) bk[i] += bk[i-1];
    for (int u = sz - 1; u >= 0; u--) ord[--bk[len_[u]]] = u;
    for (int i = sz - 1; i >= 1; i--) { int u = ord[i]; cnt[link_[u]] += cnt[u]; }

    int best = -1, bestLen = 0;
    for (int u = 1; u < sz; u++) if (cnt[u] >= 2 && len_[u] > bestLen) { bestLen = len_[u]; best = u; }

    if (best == -1) { cout << -1 << '\n'; return 0; }
    // substring of length bestLen ending at pos[best] (0-indexed inclusive)
    cout << s.substr(pos[best] - bestLen + 1, bestLen) << '\n';
    return 0;
}