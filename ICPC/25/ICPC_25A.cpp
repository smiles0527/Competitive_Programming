#include <bits/stdc++.h>
using namespace std;

struct PairInfo {
    int m, s;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S, L;
    cin >> N >> S >> L;
    int M, K, P;
    cin >> M >> K >> P;

    int spinesPerPlane = S / P;
    int oxcsPerPlane = M / P;
    int c = spinesPerPlane * K;
    int R = N * c;

    vector<int> arr(N);
    iota(arr.begin(), arr.end(), 0);

    int rounds = max(1, N - 1);

    vector<vector<int>> roundPairsA(rounds), roundPairsB(rounds);

    if (N == 2) {
        roundPairsA[0].push_back(0);
        roundPairsB[0].push_back(1);
    } else {
        vector<int> ring;
        ring.reserve(N - 1);
        for (int i = 0; i < N - 1; i++) ring.push_back(i);

        int fixed = N - 1;

        for (int r = 0; r < N - 1; r++) {
            vector<int> pos(N);
            for (int i = 0; i < N - 1; i++) pos[i] = ring[i];
            pos[N - 1] = fixed;

            for (int i = 0; i < N / 2; i++) {
                int a = pos[i];
                int b = pos[N - 1 - i];
                roundPairsA[r].push_back(a);
                roundPairsB[r].push_back(b);
            }

            int last = ring.back();
            for (int i = (int)ring.size() - 1; i >= 2; i--) ring[i] = ring[i - 1];
            ring[1] = last;
        }
    }

    vector<vector<PairInfo>> info(N, vector<PairInfo>(N, {-1, -1}));

    for (int r = 0; r < rounds; r++) {
        int m = r / c;
        int s = r % c;
        if (m >= M) m = M - 1;
        for (int t = 0; t < (int)roundPairsA[r].size(); t++) {
            int a = roundPairsA[r][t];
            int b = roundPairsB[r][t];
            int x = min(a, b), y = max(a, b);
            info[x][y] = {m, s};
        }
    }

    vector<vector<int>> conn(M, vector<int>(R, -1));
    for (int a = 0; a < N; a++) {
        for (int b = a + 1; b < N; b++) {
            auto pi = info[a][b];
            int m = pi.m, s = pi.s;
            int pa = a * c + s;
            int pb = b * c + s;
            conn[m][pa] = pb;
            conn[m][pb] = pa;
        }
    }

    for (int qi = 0; qi < 5; qi++) {
        int Q;
        cin >> Q;
        vector<array<int,4>> flows(Q);
        for (int i = 0; i < Q; i++) {
            cin >> flows[i][0] >> flows[i][1] >> flows[i][2] >> flows[i][3];
        }

        for (int m = 0; m < M; m++) {
            for (int j = 0; j < R; j++) {
                if (j) cout << ' ';
                cout << conn[m][j];
            }
            cout << '\n';
        }

        for (int i = 0; i < Q; i++) {
            int gA = flows[i][0];
            int gB = flows[i][2];
            int a = min(gA, gB);
            int b = max(gA, gB);

            auto pi = info[a][b];
            int m = pi.m, s = pi.s;

            int plane = m / oxcsPerPlane;
            int spineInPlane = s / K;
            int link = s % K;
            int spine = plane * spinesPerPlane + spineInPlane;

            int x = spine;
            int y = spine;

            cout << x << ' ' << link << ' ' << m << ' ' << y << ' ' << link << '\n';
        }
    }

    return 0;
}
