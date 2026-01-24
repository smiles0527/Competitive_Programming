#include <bits/stdc++.h>
using namespace std;

vector<int> psum(const vector<int>& arr, int n) {
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + arr[i];
    }
    return sum;
}

int main() {

    freopen("bcount.in", "r", stdin);
    freopen("bcount.out", "w", stdout);

    int n, q;
    cin >> n >> q;

    vector<int> c1(n), c2(n), c3(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        c1[i] = (x == 1);
        c2[i] = (x == 2);
        c3[i] = (x == 3);
    }

    vector<int> p1 = psum(c1, n);
    vector<int> p2 = psum(c2, n);
    vector<int> p3 = psum(c3, n);

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;

        int cow1 = p1[b] - p1[a - 1];
        int cow2 = p2[b] - p2[a - 1];
        int cow3 = p3[b] - p3[a - 1];

        cout << cow1 << " " << cow2 << " " << cow3 << "\n";
    }

    return 0;
}
