#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L, Q;
    cin >> N >> L >> Q;

    vector<int> diff(N + 2, 0);

    while (L--) {
        int P, S;
        cin >> P >> S;
        int l = max(1, P - S);
        int r = min(N, P + S);
        diff[l]++;
        if (r + 1 <= N) diff[r + 1]--;
    }

    vector<int> on(N + 1, 0);
    for (int i = 1; i <= N; i++) on[i] = on[i - 1] + diff[i];

    while (Q--) {
        int x;
        cin >> x;
        cout << (on[x] > 0 ? 'Y' : 'N') << "\n";
    }
}
