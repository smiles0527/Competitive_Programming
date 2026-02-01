#include <bits/stdc++.h>
using namespace std;

static const long long NEG = (long long)-4e18;
static const int INF = 1000000000;

struct SegMax {
    int n;
    vector<long long> t;
    SegMax() : n(0) {}
    SegMax(const vector<long long>& a) { build(a); }
    void build(const vector<long long>& a) {
        int sz = (int)a.size();
        n = 1;
        while (n < sz) n <<= 1;
        t.assign(2 * n, NEG);
        for (int i = 0; i < sz; i++) t[n + i] = a[i];
        for (int i = n - 1; i >= 1; i--) t[i] = max(t[2 * i], t[2 * i + 1]);
    }
    long long query(int l, int r) const {
        if (l > r) return NEG;
        l += n; r += n;
        long long res = NEG;
        while (l <= r) {
            if (l & 1) res = max(res, t[l++]);
            if (!(r & 1)) res = max(res, t[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

struct RMQMin {
    int n, K;
    vector<int> lg;
    vector<vector<int>> st;
    RMQMin() : n(0), K(0) {}
    RMQMin(const vector<int>& a) { build(a); }
    void build(const vector<int>& a) {
        n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        K = lg[n] + 1;
        st.assign(K, vector<int>(n));
        st[0] = a;
        for (int k = 1; k < K; k++) {
            int len = 1 << k;
            int half = len >> 1;
            for (int i = 0; i + len <= n; i++) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }
    int query(int l, int r) const {
        if (l > r) return INF;
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, F;
    cin >> N >> F;
    vector<int> a(N + 1);
    for (int i = 1; i <= N; i++) cin >> a[i];

    vector<char> farmerAt(N + 1, false);
    vector<int> farmers(F);
    for (int i = 0; i < F; i++) {
        cin >> farmers[i];
        farmerAt[farmers[i]] = true;
    }

    vector<vector<int>> rev(N + 1);
    vector<int> indeg(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        rev[a[i]].push_back(i);
        indeg[a[i]]++;
    }

    vector<char> inCycle(N + 1, true);
    queue<int> q;
    for (int i = 1; i <= N; i++) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inCycle[u] = false;
        int p = a[u];
        indeg[p]--;
        if (indeg[p] == 0) q.push(p);
    }

    vector<int> compId(N + 1, -1), cycIndex(N + 1, -1);
    vector<vector<int>> cycles;
    for (int i = 1; i <= N; i++) {
        if (!inCycle[i] || compId[i] != -1) continue;
        vector<int> nodes;
        int cur = i;
        while (compId[cur] == -1) {
            compId[cur] = (int)cycles.size();
            nodes.push_back(cur);
            cur = a[cur];
        }
        cycles.push_back(nodes);
        for (int j = 0; j < (int)nodes.size(); j++) cycIndex[nodes[j]] = j;
    }
    int C = (int)cycles.size();

    vector<int> depth(N + 1, -1), rootCycleNode(N + 1, -1);
    queue<int> qb;
    for (int i = 1; i <= N; i++) {
        if (inCycle[i]) {
            depth[i] = 0;
            rootCycleNode[i] = i;
            qb.push(i);
        }
    }
    while (!qb.empty()) {
        int u = qb.front(); qb.pop();
        for (int v : rev[u]) {
            if (inCycle[v]) continue;
            if (depth[v] != -1) continue;
            depth[v] = depth[u] + 1;
            rootCycleNode[v] = rootCycleNode[u];
            qb.push(v);
        }
    }

    vector<int> minDepthSub(N + 1, INF);
    vector<int> maxDepthSub(N + 1, -INF);
    vector<int> nonCycle;
    nonCycle.reserve(N);
    int maxD = 0;
    for (int i = 1; i <= N; i++) {
        if (!inCycle[i]) {
            nonCycle.push_back(i);
            maxD = max(maxD, depth[i]);
            if (farmerAt[i]) {
                minDepthSub[i] = depth[i];
                maxDepthSub[i] = depth[i];
            }
        }
    }

    vector<int> cnt(maxD + 1, 0);
    for (int u : nonCycle) cnt[depth[u]]++;
    for (int i = 1; i <= maxD; i++) cnt[i] += cnt[i - 1];
    vector<int> order(nonCycle.size());
    for (int u : nonCycle) order[--cnt[depth[u]]] = u;

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        int p = a[u];
        minDepthSub[p] = min(minDepthSub[p], minDepthSub[u]);
        maxDepthSub[p] = max(maxDepthSub[p], maxDepthSub[u]);
    }

    vector<long long> ans(N + 1, NEG);
    for (int i = 1; i <= N; i++) if (farmerAt[i]) ans[i] = -1;

    vector<vector<int>> treeOf(N + 1);
    for (int u = 1; u <= N; u++) {
        if (!inCycle[u]) treeOf[rootCycleNode[u]].push_back(u);
    }

    vector<vector<int>> nodesInComp(C);
    nodesInComp.assign(C, {});
    nodesInComp.reserve(C);
    for (int i = 1; i <= N; i++) {
        int cid = inCycle[i] ? compId[i] : compId[rootCycleNode[i]];
        nodesInComp[cid].push_back(i);
    }

    vector<char> compHasFarmer(C, false);
    for (int s : farmers) {
        int cid = inCycle[s] ? compId[s] : compId[rootCycleNode[s]];
        compHasFarmer[cid] = true;
    }

    for (int cid = 0; cid < C; cid++) {
        int L = (int)cycles[cid].size();

        if (!compHasFarmer[cid]) {
            for (int v : nodesInComp[cid]) if (ans[v] != -1) ans[v] = -2;
            continue;
        }

        vector<int> A(L, INF);
        for (int s : farmers) {
            int cc = inCycle[s] ? compId[s] : compId[rootCycleNode[s]];
            if (cc != cid) continue;
            int T, idxE;
            if (inCycle[s]) {
                T = 0;
                idxE = cycIndex[s];
            } else {
                int e = rootCycleNode[s];
                T = depth[s];
                idxE = cycIndex[e];
            }
            int p = idxE - (T % L);
            p %= L;
            if (p < 0) p += L;
            A[p] = min(A[p], T);
        }

        bool hasINF = false;
        for (int p = 0; p < L; p++) if (A[p] >= INF) { hasINF = true; break; }

        if (!hasINF) {
            for (int v : nodesInComp[cid]) {
                if (ans[v] == -1) continue;
                if (!inCycle[v] && minDepthSub[v] >= INF) ans[v] = -2;
                else ans[v] = -1;
            }
            continue;
        }

        vector<int> Cmin(2 * L, INF);
        for (int i = 0; i < 2 * L; i++) {
            int ap = A[i % L];
            if (ap >= INF) Cmin[i] = INF;
            else {
                long long val = (long long)ap + i;
                if (val > INF) val = INF;
                Cmin[i] = (int)val;
            }
        }
        RMQMin rmq(Cmin);

        vector<int> nextINF(2 * L, 2 * L);
        int nxt = 2 * L;
        for (int i = 2 * L - 1; i >= 0; i--) {
            if (A[i % L] >= INF) nxt = i;
            nextINF[i] = nxt;
        }

        auto cycleRests = [&](int idxC, int k) -> long long {
            int p0 = idxC - (k % L);
            p0 %= L;
            if (p0 < 0) p0 += L;
            if (A[p0] <= k) return NEG;

            int i0 = p0 + L;
            int lo = i0 - L + 1, hi = i0;
            int T = k + i0;

            int best = hi;
            int l = lo, r = hi;
            while (l <= r) {
                int mid = (l + r) >> 1;
                int mn = rmq.query(mid, i0);
                if (mn > T) {
                    best = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }

            int j = nextINF[best];
            if (j > i0) return NEG;
            return (long long)(i0 - j);
        };

        for (int v : cycles[cid]) {
            if (ans[v] == -1) continue;
            long long r = cycleRests(cycIndex[v], 0);
            if (r <= NEG / 2) ans[v] = -1;
            else ans[v] = r;
        }

        for (int cnode : cycles[cid]) {
            int D = maxDepthSub[cnode];
            if (D < 0) {
                for (int u : treeOf[cnode]) {
                    if (ans[u] == -1) continue;
                    if (minDepthSub[u] >= INF) ans[u] = -2;
                    else ans[u] = -1;
                }
                continue;
            }

            vector<long long> V(D + 1, NEG);
            int idxC = cycIndex[cnode];
            for (int k = 0; k <= D; k++) {
                long long r = cycleRests(idxC, k);
                if (r <= NEG / 2) V[k] = NEG;
                else V[k] = (long long)k + r;
            }
            SegMax seg(V);

            for (int u : treeOf[cnode]) {
                if (ans[u] == -1) continue;
                if (minDepthSub[u] >= INF) {
                    ans[u] = -2;
                    continue;
                }
                int l = depth[u];
                int r = minDepthSub[u] - 1;
                if (r > D) r = D;
                if (l > r) {
                    ans[u] = -1;
                    continue;
                }
                long long mv = seg.query(l, r);
                if (mv <= NEG / 2) ans[u] = -1;
                else ans[u] = mv - (long long)depth[u];
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        cout << (long long)ans[i] << "\n";
    }
    return 0;
}
