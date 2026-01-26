#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> arr(n);
    for (int &x : arr) cin >> x;

    int l = -1, mx = -1;
    for (int i = n - 1; i >= 0; --i) {
        mx = max(mx, arr[i]);
        if (arr[i] < mx) l = i;
    }

    if (l != -1) {
        int r = int(max_element(arr.begin() + l, arr.end()) - arr.begin());
        reverse(arr.begin() + l, arr.begin() + r + 1);
    }

    for (int i = 0; i < n; ++i) cout << arr[i] << " \n"[i + 1 == n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
    return 0;
}
