#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    vector<vector<array<int, 2>>> base = {
        {{0,0},{1,0},{1,1}},
        {{0,1},{0,2},{1,2}},
        {{0,3},{0,4},{1,4}},
        {{1,3},{2,2},{2,3}},
        {{0,5},{0,6},{1,6}},
        {{1,5},{2,4},{2,5}},
        {{0,7},{0,8},{1,8}},
        {{1,7},{2,7},{2,8}},
        {{2,6},{3,6},{3,7}},
        {{3,8},{4,7},{4,8}},
        {{3,5},{4,5},{4,6}},
        {{2,0},{2,1},{3,1}},
        {{3,0},{4,0},{4,1}},
        {{3,2},{4,2},{4,3}},
        {{3,3},{3,4},{4,4}}
    };

    while (T--) {
        int n, m;
        cin >> n >> m;

        if (n * m % 3 || n == 1 || m == 1 || (n == 3 && (m & 1)) || (m == 3 && (n & 1))) {
            cout << "NO\n";
            continue;
        }

        vector<string> a(n, string(m, '.'));
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        auto put = [&](vector<array<int, 2>> v) {
            bool bad[26] = {};

            for (auto [x, y] : v) {
                for (int z = 0; z < 4; z++) {
                    int nx = x + dx[z], ny = y + dy[z];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (a[nx][ny] != '.') bad[a[nx][ny] - 'A'] = 1;
                }
            }

            char c = 'A';
            while (bad[c - 'A']) c++;

            for (auto [x, y] : v) a[x][y] = c;
        };

        auto p23 = [&](int x, int y) {
            put({{{x,y},{x,y+1},{x+1,y}}});
            put({{{x+1,y+1},{x,y+2},{x+1,y+2}}});
        };

        auto p32 = [&](int x, int y) {
            put({{{x,y},{x,y+1},{x+1,y}}});
            put({{{x+1,y+1},{x+2,y},{x+2,y+1}}});
        };

        auto f23 = [&](int x, int y, int h, int w) {
            for (int i = x; i < x + h; i += 2) {
                for (int j = y; j < y + w; j += 3) p23(i, j);
            }
        };

        auto f32 = [&](int x, int y, int h, int w) {
            for (int i = x; i < x + h; i += 3) {
                for (int j = y; j < y + w; j += 2) p32(i, j);
            }
        };

        function<void(int,int,int,int)> go;

        auto b59 = [&](int x, int y) {
            for (auto v : base) {
                vector<array<int, 2>> cur;
                for (auto [i, j] : v) cur.push_back({x + i, y + j});
                put(cur);
            }
        };

        auto b95 = [&](int x, int y) {
            for (auto v : base) {
                vector<array<int, 2>> cur;
                for (auto [i, j] : v) cur.push_back({x + j, y + i});
                put(cur);
            }
        };

        go = [&](int x, int y, int h, int w) {
            if (!h || !w) return;

            if (h % 2 == 0) {
                if (w % 3 == 0) {
                    f23(x, y, h, w);
                } else {
                    int q = w % 3 == 1 ? 4 : 2;
                    f32(x, y, h, q);
                    f23(x, y + q, h, w - q);
                }
            } else if (w % 2 == 0) {
                if (h % 3 == 0) {
                    f32(x, y, h, w);
                } else {
                    int q = h % 3 == 1 ? 4 : 2;
                    f23(x, y, q, w);
                    f32(x + q, y, h - q, w);
                }
            } else {
                if (h % 3 == 0) {
                    b95(x, y);
                    go(x + 9, y, h - 9, 5);
                    go(x, y + 5, h, w - 5);
                } else {
                    b59(x, y);
                    go(x + 5, y, h - 5, 9);
                    go(x, y + 9, h, w - 9);
                }
            }
        };

        go(0, 0, n, m);

        cout << "YES\n";
        for (auto &s : a) cout << s << '\n';
    }
}