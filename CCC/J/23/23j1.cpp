#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int P, C;
  cin >> P >> C;

  if (P > C) {
    cout << P * 50 - C * 10 + 500;
    return 0;
  }

  cout << P * 50 - C * 10;
}
