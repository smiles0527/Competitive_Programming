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
int n, k1, k2;
vector<int> g[200005];
int sz[200005];
bool removed[200005];
ll ans = 0;

static int st0[200005], par0[200005], ord0[200005];
int subtree_size(int s) {
    int sp = 0, m = 0;
    st0[sp++] = s; par0[s] = 0;
    while (sp) {
        int u = st0[--sp];
        ord0[m++] = u;
        for (int v : g[u]) if (v != par0[u] && !removed[v]) { par0[v] = u; st0[sp++] = v; }
    }
    for (int i = m - 1; i >= 0; i--) {
        int u = ord0[i];
        sz[u] = 1;
        for (int v : g[u]) if (v != par0[u] && !removed[v]) sz[u] += sz[v];
    }
    return sz[s];
}

int find_centroid(int s, int tot) {
    int u = s, p = 0;
    while (true) {
        int nxt = -1;
        for (int v : g[u]) if (v != p && !removed[v] && sz[v] > tot/2) { nxt = v; break; }
        if (nxt == -1) break;
        sz[u] = tot - sz[nxt];
        p = u; u = nxt;
    }
    return u;
}

static int st2[200005], par2[200005], dorder[200005], depth[200005];
static ll H[200005];
static ll P[200006];
static int buf[200005], brStart[200005], brLen[200005], bidx[200005];   // branch buffer + ordering

// inline ll count_le(int* a, int len, int K) {     // #pairs i<j with a sorted, a[i]+a[j] <= K
//     if (len < 2 || K < 0) return 0;
//     ll c = 0; int j = len - 1;
//     for (int i = 0; i < len; i++) {
//         if (j < i) j = i;
//         while (j > i && a[i] + a[j] > K) j--;
//         if (j <= i) break;
//         c += (j - i);
//     }
//     return c;
// }
// inline ll count_range(int* a, int len, int lo, int hi) {
//     if (hi < lo) return 0;
//     return count_le(a, len, hi) - count_le(a, len, lo - 1);
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k1 >> k2;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    static int comp[200005];
    int csp = 0;
    comp[csp++] = 1;

    while (csp) {
        int start = comp[--csp];
        int tot = subtree_size(start);
        int c = find_centroid(start, tot);
        removed[c] = true;

//      int A = 0;
//      alld[A++] = 0;                       // centroid leg
//      for (int ch : g[c]) if (!removed[ch]) {
//          int sp = 0, m = 0;
//          st2[sp++] = ch; par2[ch] = c; depth[ch] = 1; dorder[m++] = ch;
//          while (sp) {
//              int u = st2[--sp];
//              for (int v : g[u]) if (v != par2[u] && !removed[v]) {
//                  par2[v] = u; depth[v] = depth[u] + 1;
//                  st2[sp++] = v; dorder[m++] = v;
//              }
//          }
//          int B = 0;
//          for (int i = 0; i < m; i++) { int d = depth[dorder[i]]; if (d <= k2) subd[B++] = d; }
//          sort(subd, subd + B);
//          ans -= count_range(subd, B, k1, k2);
//          for (int i = 0; i < B; i++) alld[A++] = subd[i];
//      }
//      sort(alld, alld + A);
//      ans += count_range(alld, A, k1, k2);

//      H[0] = 1;
//      int curMax = 0;
//      int kb = min(k2, tot);                       // depths beyond this never qualify
//      for (int ch : g[c]) if (!removed[ch]) {
//          int sp = 0, m = 0;
//          st2[sp++] = ch; par2[ch] = c; depth[ch] = 1; dorder[m++] = ch;
//          int cmx = 1;
//          while (sp) {
//              int u = st2[--sp];
//              for (int v : g[u]) if (v != par2[u] && !removed[v]) {
//                  int nd = depth[u] + 1;
//                  par2[v] = u; depth[v] = nd;
//                  if (nd <= kb && nd > cmx) cmx = nd;
//                  st2[sp++] = v; dorder[m++] = v;
//              }
//          }
//          int qmax = min(curMax, kb);
//          P[0] = H[0];
//          for (int d = 1; d <= qmax; d++) P[d] = P[d-1] + H[d];
//          for (int i = 0; i < m; i++) {
//              int d = depth[dorder[i]];
//              if (d > kb) continue;
//              int lo = k1 - d, hi = k2 - d;
//              if (hi < 0) continue;
//              if (lo < 0) lo = 0;
//              if (lo > qmax) continue;
//              if (hi > qmax) hi = qmax;
//              ans += P[hi] - (lo ? P[lo-1] : 0);
//          }
//          for (int i = 0; i < m; i++) {
//              int d = depth[dorder[i]];
//              if (d <= kb) H[d]++;
//          }
//          if (cmx > curMax) curMax = cmx;
//      }
//      for (int d = 0; d <= min(curMax, kb); d++) H[d] = 0;

        H[0] = 1;
        int kb = min(k2, tot);                       // depths beyond this never qualify
        int nb = 0, total = 0;
        for (int ch : g[c]) if (!removed[ch]) {      // gather each branch's depths once
            int sp = 0, m = 0;
            st2[sp++] = ch; par2[ch] = c; depth[ch] = 1; dorder[m++] = ch;
            while (sp) {
                int u = st2[--sp];
                for (int v : g[u]) if (v != par2[u] && !removed[v]) {
                    par2[v] = u; depth[v] = depth[u] + 1;
                    st2[sp++] = v; dorder[m++] = v;
                }
            }
            brStart[nb] = total; brLen[nb] = m; bidx[nb] = nb; nb++;
            for (int i = 0; i < m; i++) buf[total++] = depth[dorder[i]];
        }
        sort(bidx, bidx + nb, [](int a, int b){ return brLen[a] < brLen[b]; });  // small first -> rebuild O(subtree)

        int curMax = 0;
        for (int t = 0; t < nb; t++) {
            int b = bidx[t], st = brStart[b], len = brLen[b];
            int qmax = min(curMax, kb);
            P[0] = H[0];
            for (int d = 1; d <= qmax; d++) P[d] = P[d-1] + H[d];
            int cmx = 0;
            for (int i = 0; i < len; i++) {
                int d = buf[st + i];
                if (d > kb) continue;
                if (d > cmx) cmx = d;
                int lo = k1 - d, hi = k2 - d;
                if (hi < 0) continue;
                if (lo < 0) lo = 0;
                if (lo > qmax) continue;
                if (hi > qmax) hi = qmax;
                ans += P[hi] - (lo ? P[lo-1] : 0);
            }
            for (int i = 0; i < len; i++) { int d = buf[st + i]; if (d <= kb) H[d]++; }
            if (cmx > curMax) curMax = cmx;
        }
        for (int d = 0; d <= min(curMax, kb); d++) H[d] = 0;

        for (int ch : g[c]) if (!removed[ch]) comp[csp++] = ch;
    }

    cout << ans << '\n';
    return 0;
}