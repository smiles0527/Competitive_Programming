#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int dx[] = {1,-1,0,0}, dy[] = {0,0,1,-1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k; cin >> k;

    // prob[s][c]: probability robot from start s is at cell c after k steps
    // store as 8x8 distribution per start
    static double notland[8][8];   // product over starts of (1 - p_{s->c})
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) notland[i][j] = 1.0;

    for (int sx = 0; sx < 8; sx++)
        for (int sy = 0; sy < 8; sy++) {
            static double cur[8][8], nxt[8][8];
            for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) cur[i][j] = 0;
            cur[sx][sy] = 1.0;

            for (int step = 0; step < k; step++) {
                for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) nxt[i][j] = 0;
                for (int i = 0; i < 8; i++)
                    for (int j = 0; j < 8; j++) {
                        if (cur[i][j] == 0) continue;
                        // count valid directions
                        int cnt = 0;
                        for (int d = 0; d < 4; d++) {
                            int ni = i + dx[d], nj = j + dy[d];
                            if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8) cnt++;
                        }
                        double share = cur[i][j] / cnt;
                        for (int d = 0; d < 4; d++) {
                            int ni = i + dx[d], nj = j + dy[d];
                            if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8) nxt[ni][nj] += share;
                        }
                    }
                for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) cur[i][j] = nxt[i][j];
            }

            // multiply (1 - p) into notland
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    notland[i][j] *= (1.0 - cur[i][j]);
        }

    double ans = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            ans += notland[i][j];

    cout << fixed << setprecision(6) << ans << '\n';
    return 0;
}