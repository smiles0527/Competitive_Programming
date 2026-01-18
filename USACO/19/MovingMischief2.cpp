#include <bits/stdc++.h>
using namespace std;

struct Pt { int x, y; bool flower; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    int N, T;
    cin >> N >> T;

    vector<Pt> flowers;
    flowers.reserve(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        flowers.push_back({x, y, true});
    }

    sort(flowers.begin(), flowers.end(), [](const Pt& a, const Pt& b){
        return a.x < b.x;
    });

    vector<Pt> v;
    v.reserve(N + 2);
    v.push_back({0, 0, false});
    for (auto &p : flowers) v.push_back(p);
    v.push_back({T, T, false});

    int M = (int)v.size();
    const long long INF = (1LL << 62);

    vector<int> dpLen(M, -1);
    vector<long long> dpCost(M, INF);
    dpLen[0] = 0;
    dpCost[0] = 0;

    for (int j = 1; j < M; j++) {
        for (int i = 0; i < j; i++) {
            if (dpLen[i] < 0) continue;
            if (v[i].x < v[j].x && v[i].y < v[j].y) {
                long long add = 1LL * (v[j].x - v[i].x) * (v[j].y - v[i].y);
                int candLen = dpLen[i] + (v[j].flower ? 1 : 0);
                long long candCost = dpCost[i] + add;

                if (candLen > dpLen[j] || (candLen == dpLen[j] && candCost < dpCost[j])) {
                    dpLen[j] = candLen;
                    dpCost[j] = candCost;
                }
            }
        }
    }

    cout << dpCost[M - 1] << "\n";
    return 0;
}
