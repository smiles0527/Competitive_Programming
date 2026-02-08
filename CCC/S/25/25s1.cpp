#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a, b, c, d; cin >> a >> b >> c >> d;

  long long i = 2 * ((a+c) + max(b, d));
  long long j = 2 * (max(a, c) + (b+d));
  cout << min(i, j);
}
