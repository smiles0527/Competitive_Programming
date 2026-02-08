#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  vector<int> a;
  a.push_back(0);
  
  vector<int> x(n);
  vector<int> y(n);
  for(auto &i : x) cin >> i;
  for(auto &i : y) cin >> i;

  long long xs = 0, ys = 0;
  int ans = 0;

  for(int i=0;i<n;i++){
    xs += x[i]; ys += y[i];
    if(xs == ys) ans = i + 1;
  }

  cout << ans << '\n'; return 0;
}
