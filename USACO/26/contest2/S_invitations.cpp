#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false); 
  cin.tie(nullptr);

  int N, C; cin >> N >> C;
  vector<int> f(C + 1); for (int c = 1; c <= C; c++) cin >> f[c];
  vector<int> p(N); for (int i = 0; i < N; i++) cin >> p[i];

  vector<vector<int>> sat(N + 1);
  for (int r = 1; r <= N; r++) {
    int k; cin >> k;
    sat[r].resize(k);
    for (int j = 0; j < k; j++) cin >> sat[r][j];
    sort(sat[r].begin(), sat[r].end());
  }

  vector<priority_queue<int>> heap(C + 1);
  vector<int> ptr(N + 1, 0);
  long long sum = 0;

  auto insert_rank = [&](int r) {
    while (true) {
      if (ptr[r] >= (int)sat[r].size()) return;
      int c = sat[r][ptr[r]];

      if ((int)heap[c].size() < f[c]) {
        heap[c].push(r);
        sum += r;
        return;
      }

      int worst = heap[c].top();
      if (r < worst) {
        heap[c].pop();
        sum -= worst;
        heap[c].push(r);
        sum += r;

        r = worst;
        while (ptr[r] < (int)sat[r].size() && sat[r][ptr[r]] <= c) ptr[r]++;
      } else {
        ptr[r]++;
      }
    }
  };

  vector<long long> ans(N);
  for (int i = N - 1; i >= 0; i--) {
    int r = p[i];
    ptr[r] = 0;
    insert_rank(r);
    ans[i] = sum;
  }

  for (int i = 0; i < N; i++) cout << ans[i] << "\n";
  return 0;
}
