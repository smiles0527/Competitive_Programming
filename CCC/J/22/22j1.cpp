#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int R, S;
  cin >> R >> S;

  int n = R * 8 + S * 3;

  if (n > 28) {
    cout << n - 28;
    return 0;
  }

  cout << 28 - n;
}
