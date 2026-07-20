#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r = 0, b[30] = {};
    cin >> n;

    for (int j = 0; j < n; j++) {
        int x;
        cin >> x;
        for (int i = 29; i >= 0; i--) {
            if (!(x >> i & 1)) continue;
            if (b[i]) x ^= b[i];
            else {
                b[i] = x;
                r++;
                break;
            }
        }
    }

    cout << (1LL << r) << '\n';
}
