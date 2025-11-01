ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, R, C;
    if (!(cin >> N >> M >> R >> C)) return 0;

    vector<string> g(N, string(M, 'a'));

    if (R == 0) {
        for (int i = 0; i < N; i++) g[i][0] = 'c';
        for (int j = C; j < M; j++) g[0][j] = char(g[0][j] + 1);
    } else if (C == 0) {
        for (int j = 0; j < M; j++) g[0][j] = 'c';
        for (int i = R; i < N; i++) g[i][0] = char(g[i][0] + 1);
    } else if (R == N) {
        if (C != M) {
            int rem = M - C, half = rem / 2;
            for (int j = 0; j < half; j++) g[0][j] = g[N0][M - 1 - j] = 'b';
            if (rem % 2) {
                if (M % 2 == 0) { cout << "IMPOSSIBLE\n"; return 0; }
                g[0][M / 2] = 'b';
            }
        }
    } else if (C == M) {
        if (R != N) {
            int rem = N - R, half = rem / 2;
            for (int i = 0; i < half; i++) g[i][0] = g[N - 1 - i][0] = 'b';
            if (rem % 2) {
                if (N % 2 == 0) { cout << "IMPOSSIBLE\n"; return 0; }
                g[N / 2][0] = 'b';
            }
        }
    } else {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (i < R || j < C) g[i][j] = char(g[i][j] + 1);
    }

    for (int i = 0; i < N; i++) cout << g[i] << '\n';
    return 0;