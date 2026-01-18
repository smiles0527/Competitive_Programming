#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x, y;
    cin >> x >> y;
    string s;
    if (x > y) {
        s = "ABCD";
    } else {
        s = "BACD";
        swap(x, y);
    }

    vector<long long> reg(4);
    reg[0] = x;
    reg[1] = y;
    reg[2] = 0;
    reg[3] = 1;

    vector<array<int,3>> moves;
    auto perform_add = [&](int i, int j, int k) {
        moves.push_back({i, j, k});
        reg[k] = reg[i] + reg[j];
    };

    long long rem = y;
    while (rem > 0) {
        if (rem % 2 == 0) {
            perform_add(0, 0, 0);
            rem /= 2;
        } else {
            perform_add(0, 2, 2);
            rem -= 1;
        }
    }

    cout << moves.size() << "\n";
    for (auto &m : moves) {
        cout << s[m[0]] << " " << s[m[1]] << " " << s[m[2]] << "\n";
    }
    cout << s[2] << "\n";
    return 0;
}
