#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C;
    if (!(cin >> C)) return 0;
    vector<int> a(C), b(C);
    for (int i = 0; i < C; i++) cin >> a[i];
    for (int i = 0; i < C; i++) cin >> b[i];

    long long B = 0, E = 0;
    for (int x : a) B += x;
    for (int x : b) B += x;

    for (int i = 0; i + 1 < C; i++) {
        if (a[i] && a[i + 1]) E++;
        if (b[i] && b[i + 1]) E++;
    }

    for (int i = 0; i < C; i++) {
        if ((i % 2 == 0) && a[i] && b[i]) E++;
    }

    cout << 3 * B - 2 * E << '\n';
    return 0;
}
