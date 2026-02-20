#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    if (n < 4) {
        cout << 0 << "\n";
        return 0;
    }

    long long a = n - 1, b = n - 2, c = n - 3;
    cout << (a * b * c) / 6 << "\n";
    return 0;
}
