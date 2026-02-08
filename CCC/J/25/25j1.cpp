#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int N, C, P;
  cin >> N >> C >> P;

  if (N > C * P) { cout << "no" << '\n'; return 0;}

  cout << "yes" << '\n';
}
