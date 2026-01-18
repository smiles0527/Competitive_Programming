#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> tail;
    tail.reserve(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) tail.push_back(x);
        else *it = x;
    }

    cout << (int)tail.size() << "\n";
    return 0;
}