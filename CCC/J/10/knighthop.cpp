#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;

    if (sx == tx && sy == ty) {
        cout << 0 << "\n";
        return 0;
    }

    static int distv[9][9];
    for (int y = 1; y <= 8; y++) for (int x = 1; x <= 8; x++) distv[y][x] = -1;

    static const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    static const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

    queue<pair<int,int>> q;

    distv[sy][sx] = 0;
    q.push({sx, sy});

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        int d = distv[y][x];

        /* BFS on an unweighted graph:
           each square is a node, each legal knight move is an edge.
           first time we pop (tx,ty), we've found the minimum moves. */

        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 1 || nx > 8 || ny < 1 || ny > 8) continue;
            if (distv[ny][nx] != -1) continue;
            distv[ny][nx] = d + 1;
            if (nx == tx && ny == ty) {
                cout << distv[ny][nx] << "\n";
                return 0;
            }
            q.push({nx, ny});
        }
    }

    return 0;
}
