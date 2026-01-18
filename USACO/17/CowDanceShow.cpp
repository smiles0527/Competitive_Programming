#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;


bool finish(const vector<int>& d, int k, int tmax) {
    priority_queue<int, vector<int>, greater<int>> pq;
    int n = d.size();

    for (int i = 0; i < k; i++) pq.push(d[i]);

    for (int i = k; i < n; i++) {
        int t = pq.top();
        pq.pop();
        pq.push(t + d[i]);
    }

    int time = 0;
    while (!pq.empty()) {
        time = max(time, pq.top());
        pq.pop();
    }
    return time <= tmax;
}

int main() {

    freopen("cowdance.in", "r", stdin);
    freopen("cowdance.out", "w", stdout);

    int n, tmax;
    cin >> n >> tmax;
    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];

    int l = 1, h = n;
    while (l < h) {
        int m = l + (h - l) / 2;
        if (finish(d, m, tmax)) h = m;
        else l = m + 1;
    }

    cout << l << "\n";
    return 0;
}
