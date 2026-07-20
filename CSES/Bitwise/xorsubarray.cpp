#include <bits/stdc++.h>
using namespace std;

int tr[6000035][2], sz = 1;

void add(int x) {
    int p = 0;
    for (int i = 29; i >= 0; i--) {
        int b = x >> i & 1;
        if (!tr[p][b]) tr[p][b] = sz++;
        p = tr[p][b];
    }
}

int get(int x) {
    int p = 0, ans = 0;
    for (int i = 29; i >= 0; i--) {
        int b = x >> i & 1;
        if (tr[p][b ^ 1]) {
            ans |= 1 << i;
            p = tr[p][b ^ 1];
        } else {
            p = tr[p][b];
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x = 0, ans = 0;
    cin >> n;
    add(0);

    for (int i = 0; i < n; i++) {
        int y;
        cin >> y;
        x ^= y;
        ans = max(ans, get(x));
        add(x);
    }

    cout << ans << '\n';
}
