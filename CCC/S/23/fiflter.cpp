#include <bits/stdc++.h>
using namespace std;

bool in_cantor(long long x, long long N) {
    long long p = x;
    const int MAX_IT = 130;
    for (int it = 0; it < MAX_IT; ++it) {
        if (p == 0 || p == N) return true;
        long long threep = p * 3;
        if (threep < N) {
            p = threep;
        } else if (threep == N || threep == 2 * N) {
            return true;
        } else if (threep > 2 * N) {
            p = 3 * (N - p);
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    if (!(cin >> N)) return 0;

    vector<long long> pow3;
    pow3.push_back(1);
    while (pow3.back() < N) {
        pow3.push_back(pow3.back() * 3);
    }
    int D = (int)pow3.size() - 1;
    long long denom = pow3[D];

    vector<long long> cand;
    cand.reserve(1 << 20);

    function<void(int, long long)> dfs = [&](int level, long long val) {
        if (level == D) {
            long long L = val;
            __int128 num_min = (__int128)L * N;
            long long x_min = (long long)((num_min + denom - 1) / denom);
            __int128 num_max = (__int128)(L + 1) * N;
            long long x_max = (long long)(num_max / denom);
            if (x_min < 0) x_min = 0;
            if (x_max > N) x_max = N;
            if (x_min > x_max) return;
            cand.push_back(x_min);
            if (x_max != x_min) cand.push_back(x_max);
            return;
        }
        dfs(level + 1, val * 3);
        dfs(level + 1, val * 3 + 2);
    };

    dfs(0, 0);

    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());

    vector<long long> ans;
    ans.reserve(cand.size());
    for (long long x : cand) {
        if (in_cantor(x, N)) ans.push_back(x);
    }

    for (long long x : ans) {
        cout << x << '\n';
    }

    return 0;
}
