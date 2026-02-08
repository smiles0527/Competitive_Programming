#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int B;
  cin >> B;
  int sl = 100;

  int P = 5 * B - 400;

  if (P == sl) { cout << 0; return 0; }

  cout << (P > sl ? 1 : -1);
}
