#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    vector<int> fa(n + 1), fb(n + 1);
    for (int i = 0; i < n; i++) {
        fa[a[i]]++;
        fb[b[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        if (fa[i] != fb[i]) {
            cout << -1 << '\n';
            return 0;
        }
    }

    vector<deque<int>> pos(n + 1);
    for (int i = 0; i < n; i++) {
        pos[b[i]].push_back(i + 1);
    }

    vector<int> t(n);
    for (int i = n - 1; i >= 0; i--) {
        t[i] = pos[a[i]].front();
        pos[a[i]].pop_front();
    }

    vector<int> c(n), tops;
    for (int i = 0; i < n; i++) {
        auto it = upper_bound(tops.begin(), tops.end(), t[i]);
        if (it != tops.end()) {
            *it = t[i];
            c[i] = it - tops.begin() + 1;
        } else {
            tops.push_back(t[i]);
            c[i] = tops.size();
        }
    }

    int k = tops.size();
    vector<int> d(n + 1);
    for (int i = 0; i < n; i++) {
        d[t[i]] = c[i];
    }

    cout << k << '\n';
    for (int i = 0; i < n; i++) cout << c[i] << " \n"[i == n - 1];
    for (int i = 1; i <= n; i++) cout << d[i] << " \n"[i == n];
    return 0;
}
