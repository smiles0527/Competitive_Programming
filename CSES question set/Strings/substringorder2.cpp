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
ll occ[MX], cnt[MX];                     // occ = endpos size ; cnt = multiset of extensions

void sa_init() {
    sz = 0; last = 0;
    memset(nxt[0], -1, sizeof(nxt[0]));
    link_[0] = -1; len_[0] = 0; occ[0] = 0; sz++;
}

void sa_extend(int c) {
    int cur = sz++;
    memset(nxt[cur], -1, sizeof(nxt[cur]));
    len_[cur] = len_[last] + 1; link_[cur] = -1; occ[cur] = 1;   // primary: one endpos
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
            link_[cl] = link_[q]; occ[cl] = 0;                   // clone: no own endpos
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
    ll k; cin >> k;
    int n = s.size();

    sa_init();
    for (char ch : s) sa_extend(ch - 'a');

    // topo order by len (desc) via counting sort
    vector<int> ord(sz), bk(n + 1, 0);
    for (int u = 0; u < sz; u++) bk[len_[u]]++;
    for (int i = 1; i <= n; i++) bk[i] += bk[i-1];
    for (int u = sz - 1; u >= 0; u--) ord[--bk[len_[u]]] = u;

    // occ propagation up the link tree (children before parent => reverse topo by len)
    for (int i = sz - 1; i >= 1; i--) { int u = ord[i]; occ[link_[u]] += occ[u]; }

    // cnt[u] = sum over edges (occ[child] + cnt[child]); longest first
    for (int i = sz - 1; i >= 0; i--) {
        int u = ord[i];
        cnt[u] = 0;
        for (int c = 0; c < 26; c++) {
            int v = nxt[u][c];
            if (v != -1) cnt[u] += occ[v] + cnt[v];
        }
    }

    // greedy descent from root
    string out;
    int u = 0;
    while (k > 0) {
        for (int c = 0; c < 26; c++) {
            int v = nxt[u][c];
            if (v == -1) continue;
            ll here = occ[v] + cnt[v];        // substrings (with mult.) using this edge
            if (k <= occ[v]) { out += char('a' + c); k = 0; break; }   // prefix+c is the answer
            if (k <= here) { out += char('a' + c); k -= occ[v]; u = v; break; }
            k -= here;
        }
    }
    cout << out << '\n';
    return 0;
}