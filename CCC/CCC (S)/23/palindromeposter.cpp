#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, R, C;
    if (!(cin >> N >> M >> R >> C)) return 0;

    if (N == 2 && M == 2) {
        set<pair<int, int>> ok{ {0,0},{0,2},{1,1},{2,0},{2,2} };
        if (!ok.count({ R,C })) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<string> g(N, string(M, 'a'));

    int pairsR = N / 2;
    int pairsC = M / 2;
    int midR = (N % 2 ? N / 2 : -1);
    int midC = (M % 2 ? M / 2 : -1);

    // Step 1: set exactly C palindromic columns
    for (int j = 0; j < M; j++) {
        bool makePal = (j < C);
        for (int p = 0; p < pairsR; p++) {
            int i1 = p;
            int i2 = N - 1 - p;
            if (makePal) {
                g[i1][j] = 'a';
                g[i2][j] = 'a';
            }
            else {
                g[i1][j] = 'a';
                g[i2][j] = 'b';
            }
        }
        if (midR != -1) g[midR][j] = 'a';
    }

    // Now all rows are pal (equal within every column-pair). We need exactly R pal rows.
    int wantPal = R;
    vector<int> willBePal(N, 0);

    // Mark which rows should remain pal: take first R rows (any choice works)
    for (int i = 0; i < N && wantPal > 0; i++, wantPal--) willBePal[i] = 1;

    // Step 2: break the other rows to non-pal using column-pairs
    int x = 0, y = M -
