#include <bits/stdc++.h>
using namespace std;

int main() {

    long long n;
    cin >> n;

    long long l = 1, h = 2e10;
    while (l < h) {
        long long m = (l + h) / 2;
        long long moo = m / 3 + m / 5 - m / 15;
        long long spoken = m - moo;
        if (spoken >= n) h = m;
        else l = m + 1;
    }

    cout << l << "\n";
    return 0;
}
