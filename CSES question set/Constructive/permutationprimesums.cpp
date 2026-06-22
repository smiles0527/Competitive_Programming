#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int N = 2 * n + 5;
    vector<int> prime(N, 1), nxt(N + 1), b(n + 1);

    prime[0] = prime[1] = 0;
    for (int i = 2; i * i < N; i++) {
        if (prime[i]) {
            for (int j = i * i; j < N; j += i) prime[j] = 0;
        }
    }

    int last = -1;
    for (int i = N - 1; i >= 0; i--) {
        if (prime[i]) last = i;
        nxt[i] = last;
    }

    for (int m = n; m;) {
        int p = nxt[m + 1];
        int l = p - m;
        for (int x = l; x <= m; x++) b[x] = p - x;
        m = l - 1;
    }

    for (int i = 1; i <= n; i++) cout << i << ' ';
    cout << '\n';

    for (int i = 1; i <= n; i++) cout << b[i] << ' ';
    cout << '\n';
}