#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    unordered_map<unsigned long long, int> best;
    best.reserve(4000007);
    best.max_load_factor(0.7f);

    const unsigned long long BASE = 1315423911ULL;

    long long ans = 0;
    string s;
    vector<int> pi;
    vector<unsigned long long> pref;

    for (int it = 0; it < n; ++it) {
        cin >> s;
        int len = (int)s.size();

        pi.assign(len, 0);
        for (int i = 1; i < len; ++i) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) ++j;
            pi[i] = j;
        }

        pref.assign(len, 0);
        unsigned long long h = 0;
        for (int i = 0; i < len; ++i) {
            h = h * BASE + (unsigned long long)(s[i] - 'A' + 1);
            pref[i] = h;
        }

        int dp_here = 1;
        int L = len;
        while (L > 0) {
            unsigned long long hh = pref[L - 1];
            auto it2 = best.find(hh);
            if (it2 != best.end()) {
                int cand = it2->second + 1;
                if (cand > dp_here) dp_here = cand;
            }
            L = pi[L - 1];
        }

        unsigned long long full_hash = pref[len - 1];
        auto it3 = best.find(full_hash);
        if (it3 == best.end()) {
            best.emplace(full_hash, dp_here);
        } else if (dp_here > it3->second) {
            it3->second = dp_here;
        }

        if (dp_here > ans) ans = dp_here;
    }

    cout << ans << '\n';
    return 0;
}
