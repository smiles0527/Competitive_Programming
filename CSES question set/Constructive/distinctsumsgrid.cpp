#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n < 4) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<vector<int>> a(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) a[i][j] = i + 1;
    }

    int m = n / 2;

    for (int h = 1; h <= m; h++) {
        int r = h - 1;
        for (int x = h; x <= m; x++) {
            int neg = x - 1;
            int pos = (n & 1) ? m + x : m + x - 1;
            swap(a[r][pos], a[r + 1][neg]);
        }
    }

    if (n & 1) {
        swap(a[m][m - 1], a[n - 1][m - 1]);
        swap(a[m][m], a[m + 1][m]);
    } else {
        swap(a[m][m - 1], a[n - 1][m - 1]);
    }

    string out;
    out.reserve((size_t)n * n * 5);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out += to_string(a[i][j]);
            out += ' ';
        }
        out += '\n';
    }

    cout << out;
}