
#include <bits/stdc++.h>
using namespace std;
/*
  A board can be represented as a bitmask:
  bit i = 1 --> cell i is M
  bit i = 0 --> cell i is O

  For a move (x, y, z) to score:
  - x must be M
  - y and z must be O

  So, let b_i = 1 if cell is M. So a move scores if:

  bx(1-by)(1-bz) = bx - bxby - bxbz + bxbybz
  
  each move thus contributes:
  +1 to subset {x}
  -1 to {x, y}
  -1 to {x, z}
  +1 to {x, y, z}
  we store all of these values in an array a[mask] intended by bitmamsk

  We must iterate through every possible subset T of the superset mask and compute the cumulative
  sum of their corresponding values (Sum over Subsets DP)

  the idea is like this:
      for each bit b:
        for each mask containing b:
          a[mask] += a[mask without b]
  
  after this, a[mask] equals the score of that board

  Finally, we
  - find the maximum score
  - count how many masks achieve it
  
  Complexity: 
  2^N (with N<=20) for states
  Time: O(N * 2^N)
  Space: O(2^N)


 */
void solve() {
    int N, K; cin >> N >> K;

    int M = 1 << N;
    vector<long long> a(M, 0);

    for (int i = 0; i < K; i++) {
        int x, y, z; cin >> x >> y >> z;
        x--; y--; z--;

        int mx = 1 << x;
        int mxy = mx | (1 << y);
        int mxz = mx | (1 << z);
        int mxyz = mxy | (1 << z);

        a[mx] += 1;
        a[mxy] -= 1;
        a[mxz] -= 1;
        a[mxyz] += 1;
    }

    for (int b = 0; b < N; b++) {
        for (int mask = 0; mask < M; mask++) {
            if (mask & (1 << b)) a[mask] += a[mask ^ (1 << b)];
        }
    }

    long long best = a[0], cnt = 0;
    for (int mask = 0; mask < M; mask++) best = max(best, a[mask]);
    for (int mask = 0; mask < M; mask++) if (a[mask] == best) cnt++;

    cout << best << " " << cnt << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}
