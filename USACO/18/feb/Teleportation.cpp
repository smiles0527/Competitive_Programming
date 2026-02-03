#include <bits/stdc++.h>
using namespace std;

int main() {

    int a, b, x, y;
    cin >> a >> b >> x >> y;

    int d0 = abs(a - b);
    int d1 = abs(a - x) + abs(b - y);
    int d2 = abs(a - y) + abs(b - x);

    cout << min(d0, min(d1, d2)) << "\n";
    return 0;
}
    