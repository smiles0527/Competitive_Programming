#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<pair<long long, long long>> jobs;
        jobs.reserve(n);

        for (int i = 0; i < n; i++) {
            long long s, t;
            cin >> s >> t;
            long long d = s + t;
            jobs.push_back({d, t});
        }

        sort(jobs.begin(), jobs.end());

        priority_queue<long long> pq;
        long long total = 0;

        for (auto &jt : jobs) {
            long long d = jt.first;
            long long t = jt.second;
            total += t;
            pq.push(t);
            if (total > d) {
                total -= pq.top();
                pq.pop();
            }
        }

        cout << (int)pq.size() << "\n";
    }
    return 0;
}