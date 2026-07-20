#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    ll x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    vector<int> qv(k), qi(k);
    int head = 0, sz = 0;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (sz && qi[head] <= i - k) {
            head++;
            if (head == k) {
                head = 0;
            }
            sz--;
        }

        while (sz) {
            int p = head + sz - 1;
            if (p >= k) {
                p -= k;
            }

            if (qv[p] < x) {
                break;
            }

            sz--;
        }

        int p = head + sz;
        if (p >= k) {
            p -= k;
        }

        qv[p] = x;
        qi[p] = i;
        sz++;

        if (i >= k - 1) {
            ans ^= qv[head];
        }

        x = (a * x + b) % c;
    }

    cout << ans << '\n';
}
