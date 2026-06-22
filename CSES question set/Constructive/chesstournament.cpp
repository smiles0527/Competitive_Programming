#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    priority_queue<pair<int, int>> pq;
    long long sum = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x < 0 || x >= n) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        sum += x;
        if (x) pq.push({x, i});
    }

    if (sum & 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<pair<int, int>> ans;

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if ((int)pq.size() < d) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }

        vector<pair<int, int>> take;

        while (d--) {
            auto [x, u] = pq.top();
            pq.pop();

            ans.push_back({v, u});

            --x;
            if (x < 0) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }

            if (x) take.push_back({x, u});
        }

        for (auto e : take) pq.push(e);
    }

    cout << ans.size() << '\n';
    for (auto [u, v] : ans) cout << u << ' ' << v << '\n';
}