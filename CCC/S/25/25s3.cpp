#include <bits/stdc++.h>
using namespace std;

static const long long NEG = (long long)-4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, Q; cin >> N >> K >> Q;

    vector<int> col(N + 1);
    vector<long long> pre(N + 1);

    vector<multiset<long long>> ms(K + 1);
    for (int i = 1; i <= N; i++) {
        int c;
        long long p;
        cin >> c >> p;
        col[i] = c;
        pre[i] = p;
        ms[c].insert(p);
    }

    vector<long long> mx1(K + 1, 0), mx2(K + 1, NEG);
    multiset<pair<long long,int>> s1;
    multiset<pair<long long,int>> s2;
    long long S = 0;

    auto recalc = [&](int c) {
        auto it1 = s1.find({mx1[c], c});
        if (it1 != s1.end()) s1.erase(it1);
        S -= mx1[c];

        if (mx2[c] != NEG) {
            auto it2 = s2.find({mx2[c], c});
            if (it2 != s2.end()) s2.erase(it2);
        }

        auto &m = ms[c];
        mx1[c] = *m.rbegin();
        if ((int)m.size() >= 2) {
            auto it = m.end();
            --it;
            --it;
            mx2[c] = *it;
        } else {
            mx2[c] = NEG;
        }

        s1.insert({mx1[c], c});
        S += mx1[c];
        if (mx2[c] != NEG) s2.insert({mx2[c], c});
    };

    for (int c = 1; c <= K; c++) recalc(c);

    auto answer = [&]() -> long long {
        auto it = s1.begin();
        long long mn1 = it->first;
        int m = it->second;

        long long mn2 = mn1;
        if (K >= 2) {
            auto it2 = it;
            ++it2;
            mn2 = it2->first;
        }

        long long best = 0;

        if (!s2.empty()) {
            auto itmax = prev(s2.end());
            long long v1 = itmax->first;
            int c1 = itmax->second;
            long long bestExcl = NEG;
            if (c1 != m) bestExcl = v1;
            else if ((int)s2.size() >= 2) {
                auto itmax2 = itmax;
                --itmax2;
                bestExcl = itmax2->first;
            }
            if (bestExcl != NEG) best = max(best, bestExcl - mn1);
        }

        if (K >= 2 && mx2[m] != NEG) best = max(best, mx2[m] - mn2);

        if (best < 0) best = 0;
        return S + best;
    };

    cout << answer() << "\n";

    for (int qq = 0; qq < Q; qq++) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, c;
            cin >> i >> c;
            int oc = col[i];
            if (oc != c) {
                ms[oc].erase(ms[oc].find(pre[i]));
                ms[c].insert(pre[i]);
                col[i] = c;
                recalc(oc);
                recalc(c);
            }
        } else {
            int i;
            long long p;
            cin >> i >> p;
            int c = col[i];
            ms[c].erase(ms[c].find(pre[i]));
            ms[c].insert(p);
            pre[i] = p;
            recalc(c);
        }
        cout << answer() << "\n";
    }

    return 0;
}
