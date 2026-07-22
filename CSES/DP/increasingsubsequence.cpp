#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> tail;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        int p = lower_bound(tail.begin(), tail.end(), x) - tail.begin();

        if (p == (int)tail.size()) tail.push_back(x);
        else tail[p] = x;
    }

    cout << tail.size() << '\n';
}
