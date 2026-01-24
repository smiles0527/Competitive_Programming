#include <bits/stdc++.h>
using namespace std;

/*

Once a1 is known, ai+1 is determined as bi - ai.
So the problem is just finding the smallest possible a1 that yields a valid permutation.

*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("photo.in", "r", stdin);   
    // freopen("photo.out", "w", stdout);

    int N;
    cin >> N;
    vector<int> b(N - 1);
    for (int i = 0; i < N - 1; i++) cin >> b[i];

    for (int first = 1; first <= N; first++) {
        vector<int> a(N);
        vector<char> seen(N + 1, false);
        bool ok = true;

        a[0] = first;
        seen[first] = true;

        for (int i = 0; i < N - 1; i++) {
            // Once a1 is known, ai+1 is determined
            a[i + 1] = b[i] - a[i];
            int v = a[i + 1];
            // When reconstructing, immediately reject if 1) out of [1, N] or 2) already seen
            if (v < 1 || v > N || seen[v]) {
                ok = false;
                break;
            }
            seen[v] = true;
        }

        if (ok) {
            for (int i = 0; i < N; i++) {
                if (i) cout << ' ';
                cout << a[i];
            }
            cout << '\n';
            return 0;
        }
    }
    return 0;
}
