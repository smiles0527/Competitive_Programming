#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string needle, hay;
    cin >> needle >> hay;
    int m = needle.size(), n = hay.size();
    if (m > n) {
        cout << 0 << "\n";
        return 0;
    }

    int need[26] = {0}, win[26] = {0};
    for (char c : needle) need[c - 'a']++;
    for (int i = 0; i < m; i++) win[hay[i] - 'a']++;

    unordered_set<string> found;
    if (equal(begin(need), end(need), begin(win)))
        found.insert(hay.substr(0, m));

    for (int i = m; i < n; i++) {
        win[hay[i] - 'a']++;
        win[hay[i - m] - 'a']--;
        if (equal(begin(need), end(need), begin(win)))
            found.insert(hay.substr(i - m + 1, m));
    }

    cout << found.size() << "\n";
}
