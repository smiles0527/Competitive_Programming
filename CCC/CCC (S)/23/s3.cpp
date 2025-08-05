#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, R, C;
    if (!(cin >> N >> M >> R >> C)) return 0;

    auto bad = [] { cout << "IMPOSSIBLE\n"; exit(0); };

    if (R > N || C > M) bad();

    if (N == 1 && M == 1) {
        if (R == 1 && C == 1) { cout << "a\n"; return 0; }
        bad();
    }

    if (N == 1) {
        if (C != M) bad();
        string row(M, 'a');
        if (R == 0) row[M - 1] = 'b';
        else if (R != 1) bad();
        cout << row << '\n';
        return 0;
    }

    if (M == 1) {
        if (R != N) bad();
        vector<string> g(N, string(1, 'a'));
        if (C == 0) g[0][0] = 'b';
        else if (C != 1) bad();
        for (auto &s : g) cout << s << '\n';
        return 0;
    }

    vector<string> g(N, string(M, 'a'));

    if (R < N && C < M) {
        for (int i = R; i < N; ++i)
            for (int j = C; j < M; ++j)
                g[i][j] = 'b';
    } else if (R == 0 && C < M) {
        for (int i = 0; i < N; ++i) g[i][M - 1] = 'b';
        int need = M - C, done = 0;
        for (int j = M - 2; j >= 0 && done < need; --j) {
            g[N - 1][j] = 'c';
            ++done;
        }
        if (done < need) g[0][M - 1] = 'c';
    } else if (C == 0 && R < N) {
        for (int j = 0; j < M; ++j) g[N - 1][j] = 'b';
        int need = N - R, done = 0, idx = 0;
        for (int i = N - 2; i >= 0 && done < need; --i) {
            g[i][0] = char('c' + (idx++ % 24));
            ++done;
        }
        if (done < need) {
            int col = (M > 1 ? 1 : 0);
            g[N - 1][col] = char('c' + (idx++ % 24));
        }
    } else if (R == N) {
        int need = M - C;
        if (need < 0) bad();
        if ((M % 2 == 0) && (need % 2)) bad();
        int j = 0;
        while (need >= 2) {
            g[0][j] = g[0][M - 1 - j] = 'b';
            need -= 2;
            ++j;
        }
        if (need == 1) g[0][M / 2] = 'b';
    } else if (C == M) {
        int need = N - R;
        if (need < 0) bad();
        if ((N % 2 == 0) && (need % 2)) bad();
        int i = 0;
        while (need >= 2) {
            g[i][0] = g[N - 1 - i][0] = 'b';
            need -= 2;
            ++i;
        }
        if (need == 1) g[N / 2][0] = 'b';
    } else bad();

    for (auto &row : g) cout << row << '\n';
    return 0;
}
