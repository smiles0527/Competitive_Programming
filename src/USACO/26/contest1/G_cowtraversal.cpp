// 7/21

#include <bits/stdc++.h>
using namespace std;


struct fenw {
    int n;
    vector<long long> b;
    fenw() : n(0) {}
    fenw(int n_) { init(n_); }
    void init(int n_) {
        n = n_;
        b.assign(n + 1, 0);
    }
    void add(int i, long long v) {
        for (; i <= n; i += i & -i) b[i] += v;
    }
    long long sum(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += b[i];
        return s;
    }
    long long sum(int l, int r) const {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};


struct seg {
    int n0, n;
    vector<int> st;
    const vector<int> *dep;

    void init(int n_, const vector<int> *d_) {
        n0 = n_;
        dep = d_;
        n = 1;
        while (n < n0) n <<= 1;
        st.assign(2 * n, -1);
    }
    int better(int u, int v) const {
        if (u == -1) return v;
        if (v == -1) return u;
        return ((*dep)[u] >= (*dep)[v]) ? u : v;
    }
    void setp(int i, int v) {
        i += n;
        st[i] = v;
        for (i >>= 1; i; i >>= 1) st[i] = better(st[i << 1], st[i << 1 | 1]);
    }
    int qry(int l, int r) const {
        int L = -1, R = -1;
        l += n; r += n;
        while (l <= r) {
            if (l & 1) L = better(L, st[l++]);
            if (!(r & 1)) R = better(st[r--], R);
            l >>= 1; r >>= 1;
        }
        return better(L, R);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<int>> radj(n + 1);
    for (int i = 1; i <= n; i++) radj[a[i]].push_back(i);

    int m;
    cin >> m;
    vector<int> c(m + 1);
    vector<char> t(m + 1);
    for (int i = 1; i <= m; i++) cin >> c[i] >> t[i];

    
    vector<int> stt(n + 1, 0), inc(n + 1, 0), cid(n + 1, -1), pos(n + 1, -1);
    vector<vector<int>> cyc;
    vector<int> stk;

    for (int i = 1; i <= n; i++) {
        if (stt[i]) continue;
        int u = i;
        while (!stt[u]) {
            stt[u] = 1;
            stk.push_back(u);
            u = a[u];
        }
        if (stt[u] == 1) {
            vector<int> v;
            while (true) {
                int x = stk.back(); stk.pop_back();
                v.push_back(x);
                inc[x] = 1;
                if (x == u) break;
            }
            reverse(v.begin(), v.end());
            int id = (int)cyc.size();
            cyc.push_back(v);
            for (int j = 0; j < (int)v.size(); j++) {
                cid[v[j]] = id;
                pos[v[j]] = j;
            }
        }
        while (!stk.empty() && stt[stk.back()] == 1) {
            stt[stk.back()] = 2;
            stk.pop_back();
        }
    }

    
    vector<vector<int>> tadj(n + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : radj[u]) {
            if (inc[v]) continue;
            tadj[u].push_back(v);
        }
    }

    
    vector<int> rrt(n + 1, -1), dep(n + 1, 0), sz(n + 1, 1), hv(n + 1, -1);
    vector<int> tin(n + 1, 0), tout(n + 1, 0);
    int tim = 0;

    vector<int> q;
    q.reserve(n);

    for (auto &v : cyc) {
        for (int r : v) {
            dep[r] = 0;
            rrt[r] = r;
            q.push_back(r);
        }
    }

    int head = 0;
    while (head < (int)q.size()) {
        int u = q[head++];
        for (int v : tadj[u]) {
            dep[v] = dep[u] + 1;
            rrt[v] = rrt[u];
            q.push_back(v);
        }
    }

    for (int i = (int)q.size() - 1; i >= 0; i--) {
        int u = q[i];
        sz[u] = 1;
        int best = 0;
        for (int v : tadj[u]) {
            sz[u] += sz[v];
            if (sz[v] > best) {
                best = sz[v];
                hv[u] = v;
            }
        }
    }

    
    vector<int> iter_stk;
    vector<int> cur_edge(n + 1, 0);

    for (auto &v : cyc) {
        for (int r : v) {
            iter_stk.push_back(r);
            tin[r] = ++tim;
            while (!iter_stk.empty()) {
                int u = iter_stk.back();
                if (cur_edge[u] < (int)tadj[u].size()) {
                    int v_child = tadj[u][cur_edge[u]++];
                    tin[v_child] = ++tim;
                    iter_stk.push_back(v_child);
                } else {
                    tout[u] = tim;
                    iter_stk.pop_back();
                }
            }
        }
    }

    
    vector<int> hd(n + 1, 0), par(n + 1, 0), hpos(n + 1, 0);
    int cur = 0;

    for (auto &v : cyc) {
        for (int r : v) {
            vector<pair<int, int>> hld_stk;
            hld_stk.push_back({r, r});

            while (!hld_stk.empty()) {
                pair<int, int> top = hld_stk.back();
                hld_stk.pop_back();
                int u = top.first;
                int h = top.second;

                hd[u] = h;
                hpos[u] = cur++;

                for (int v_child : tadj[u]) {
                    if (v_child != hv[u]) {
                        par[v_child] = u;
                        hld_stk.push_back({v_child, v_child});
                    }
                }
                if (hv[u] != -1) {
                    par[hv[u]] = u;
                    hld_stk.push_back({hv[u], h});
                }
            }
        }
    }

    
    seg sg;
    sg.init(cur, &dep);

    fenw bit_tree(tim);

    int cc = (int)cyc.size();
    vector<set<int>> asetcyc(cc);
    vector<fenw> fw(cc);
    for (int id = 0; id < cc; id++) fw[id].init((int)cyc[id].size());

    vector<long long> rem(n + 1, 0);
    for (int id = 0; id < cc; id++) {
        for (int x : cyc[id]) {
            rem[x] = sz[x];
            fw[id].add(pos[x] + 1, rem[x]);
        }
    }

    vector<char> act(n + 1, 0), tp(n + 1, 0);
    vector<long long> bas(n + 1, 0);

    long long tc = 0, to = 0, tw = 0;

    auto addt = [&](char x, long long v) {
        if (x == 'C') tc += v;
        else if (x == 'O') to += v;
        else tw += v;
    };
    auto subt = [&](char x, long long v) {
        if (x == 'C') tc -= v;
        else if (x == 'O') to -= v;
        else tw -= v;
    };

    auto up = [&](int u) {
        sg.setp(hpos[u], act[u] ? u : -1);
    };

    auto hqry = [&](int u, int r) -> int {
        int ans = -1;
        while (u && hd[u] != hd[r]) {
            int got = sg.qry(hpos[hd[u]], hpos[u]);
            if (got != -1 && (ans == -1 || dep[got] > dep[ans])) ans = got;
            u = par[hd[u]];
        }
        if (u) {
            int got = sg.qry(hpos[r], hpos[u]);
            if (got != -1 && (ans == -1 || dep[got] > dep[ans])) ans = got;
        }
        return ans;
    };

    auto nxt_after = [&](int id, int p) -> int {
        auto &s = asetcyc[id];
        if (s.empty()) return 0;
        auto it = s.upper_bound(p);
        if (it == s.end()) it = s.begin();
        return cyc[id][*it];
    };

    auto prv = [&](int id, int p) -> int {
        auto &s = asetcyc[id];
        if (s.empty()) return -1;
        auto it = s.lower_bound(p);
        if (it == s.begin()) it = s.end();
        --it;
        return *it;
    };

    auto sumcyc = [&](int id, int l, int r) -> long long {
        int L = (int)cyc[id].size();
        if (l <= r) return fw[id].sum(l + 1, r + 1);
        return fw[id].sum(l + 1, L) + fw[id].sum(1, r + 1);
    };

    auto dest = [&](int u) -> int {
        int r = rrt[u];
        int x = hqry(u, r);
        if (x != -1) return x;
        return nxt_after(cid[r], pos[r]);
    };

    auto dec_rem = [&](int r, long long d) {
        if (d == 0) return;
        int id = cid[r];
        rem[r] -= d;
        fw[id].add(pos[r] + 1, -d);
    };

    auto activate = [&](int u, char nt) {
        int p = dest(u);

        long long covered = bit_tree.sum(tin[u], tout[u]);
        long long unc = (long long)sz[u] - covered;

        act[u] = 1;
        tp[u] = nt;
        bas[u] = unc;

        bit_tree.add(tin[u], unc);
        up(u);

        addt(tp[u], unc);

        if (p) {
            subt(tp[p], unc);
            bas[p] -= unc;

            if (rrt[p] == rrt[u]) {
                bit_tree.add(tin[p], -unc);
            }
        }

        if (!inc[u]) {
            if (!act[rrt[u]] && (p == 0 || inc[p])) {
                dec_rem(rrt[u], unc);
            }
            return;
        }

        
        int id = cid[u];
        int pu = pos[u];

        long long cur_rem = rem[u];
        if (cur_rem) {
            dec_rem(u, cur_rem);
        }

        if (asetcyc[id].empty()) {
            asetcyc[id].insert(pu);
            long long tot = fw[id].sum((int)cyc[id].size());
            bas[u] += tot;
            addt(tp[u], tot);
            return;
        }

        int pv = prv(id, pu);
        int s = nxt_after(id, pu);

        asetcyc[id].insert(pu);

        int l = (pv + 1) % (int)cyc[id].size();
        int r = pu;

        long long gain = sumcyc(id, l, r);

        bas[u] += gain;
        addt(tp[u], gain);

        if (s) {
            subt(tp[s], gain);
            bas[s] -= gain;
        }
    };

    for (int i = 1; i <= m; i++) {
        int u = c[i];
        char nt = t[i];

        if (!act[u]) {
            activate(u, nt);
        } else if (tp[u] != nt) {
            subt(tp[u], bas[u]);
            tp[u] = nt;
            addt(tp[u], bas[u]);
        }

        cout << tc << " " << to << " " << tw << "\n";
    }

    return 0;
}   