#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    vector<vector<int>> positions(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        positions[v[i]].push_back(i);
    }
    vector<int> ans(n + 1);
    int B = min(n, 50);
    for (int val = 1; val <= n; val++) {
        auto &p = positions[val];
        if (p.empty()) continue;
        int contrib;
        for (int sz = 1; sz <= B; sz++) {
            int lst = p[0];
            int cnt = 1;
            for (int j = 1; j < (int)p.size(); j++) {
                if (p[j] - lst > sz) {
                    cnt++;
                    lst = p[j];
                }
            }
            if (sz == 1) {
                ans[1] += cnt;
            } else {
                ans[sz] -= (contrib - cnt);
            }
            contrib = cnt;
        }
        vector<int> beginnings;
        beginnings.push_back(p[0]);
        int smallest = n + 1;
        for (int j = 1; j < (int)p.size(); j++) {
            if (p[j] - beginnings.back() > B) {
                smallest = min(smallest, p[j] - beginnings.back());
                beginnings.push_back(p[j]);
            }
        }
        while ((int)beginnings.size() > 1) {
            int j = 0;
            int cnt = 1;
            int smallest2 = n + 1;
            while (j < (int)p.size()) {
                int L = j;
                int R = (int)p.size() - 1;
                int idx = R + 1;
                while (L <= R) {
                    int mid = (L + R) / 2;
                    if (p[mid] - p[j] > smallest) {
                        idx = mid;
                        R = mid - 1;
                    } else {
                        L = mid + 1;
                    }
                }
                if (idx < (int)p.size()) {
                    smallest2 = min(smallest2, p[idx] - beginnings[cnt - 1]);
                    beginnings[cnt] = p[idx];
                    cnt++;
                }
                j = idx;
            }
            ans[smallest] -= (int)beginnings.size() - cnt;
            smallest = smallest2;
            while ((int)beginnings.size() > cnt) beginnings.pop_back();
        }
    }
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
        cout << ans[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}
