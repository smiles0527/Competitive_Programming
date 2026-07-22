#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    deque<int> q;
    for (int i = 1; i <= n; i++) q.push_back(i);
    bool first = true;
    while (!q.empty()) {
        q.push_back(q.front()); q.pop_front();
        if (!first) cout << ' ';
        first = false;
        cout << q.front();
        q.pop_front();
    }
    cout << '\n';
}
