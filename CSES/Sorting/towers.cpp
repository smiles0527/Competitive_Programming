#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<int> top;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;

        auto it = upper_bound(top.begin(), top.end(), x);

        if (it == top.end()) top.push_back(x);
        else *it = x;
    }

    cout << top.size() << '\n';
}
