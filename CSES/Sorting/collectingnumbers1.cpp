#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<int> pos(n + 1);

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        pos[x] = i;
    }

    int ans = 1;

    for (int x = 2; x <= n; x++) {
        if (pos[x] < pos[x - 1]) ans++;
    }

    cout << ans << '\n';
}
