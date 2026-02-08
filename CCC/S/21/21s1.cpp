#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  vector<int> h(n+1); for(auto &x: h) cin >> x;
  vector<int> w(n); for(auto &x : w) cin >> x;

  double area = 0.0;
  for(int i = 0; i < n; i++){
    area += (h[i] + h[i+1]) * w[i] / 2.0;
  }
  cout << fixed << area << '\n'; return 0;
}
