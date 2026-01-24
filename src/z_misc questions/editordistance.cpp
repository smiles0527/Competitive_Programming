#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> lineLength(n);
    for (int i = 0; i < n; i++) cin >> lineLength[i];

    int rs, cs, rf, cf;
    cin >> rs >> cs >> rf >> cf;
    rs--; cs--; rf--; cf--;

    queue<pair<int, int>> q;
    q.push({rs, cs});
    vector<vector<bool>> visited(n);
    for (int i = 0; i < n; i++) visited[i].resize(lineLength[i], false);
    visited[rs][cs] = true;

    int steps = 0;
    int dir[4][2] = {{0,1},{0,-1},{-1,0},{1,0}}; //RLUD

    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto [r, c] = q.front();
            q.pop();
            if (r == rf && c == cf) {
                cout << steps << '\n';
                return 0;
            }

            //R 
            if (c + 1 < lineLength[r] && !visited[r][c + 1]) {
                visited[r][c + 1] = true;
                q.push({r, c + 1});
            } else if (c + 1 == lineLength[r] && r + 1 < n && !visited[r + 1][0]) {
                visited[r + 1][0] = true;
                q.push({r + 1, 0}); 
            }

            //L
            if (c - 1 >= 0 && !visited[r][c - 1]) {
                visited[r][c - 1] = true;
                q.push({r, c - 1});
            } else if (c == 0 && r - 1 >= 0 && !visited[r - 1][lineLength[r - 1] - 1]) {
                visited[r - 1][lineLength[r - 1] - 1] = true;
                q.push({r - 1, lineLength[r - 1] - 1});
            }

            //U
            if (r - 1 >= 0) {
                int nc = c < lineLength[r - 1] ? c : lineLength[r - 1] - 1;
                if (!visited[r - 1][nc]) {
                    visited[r - 1][nc] = true;
                    q.push({r - 1, nc});
                 }
            }

            //D
            if (r + 1 < n) {
                int nc = c < lineLength[r + 1] ? c : lineLength[r + 1] - 1;
                if (!visited[r + 1][nc]) {
                    visited[r + 1][nc] = true;
                    q.push({r + 1, nc});
                }
            }
        }
        steps++;
    }
}
