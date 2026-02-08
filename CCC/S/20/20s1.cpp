#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n; cin >> n;
  vector<pair<int, int>> a(n);
  for(int i = 0; i < n; i++) cin>> a[i].first >> a[i].second;
  sort(a.begin(), a.end());
  
  double best = 0.0;
  for(int i = 0; i + 1 < n; i++){
    int dt = a[i+1].first - a[i].first;
    int dx = a[i+1].second - a[i].second;
    double v = (double)abs(dx) / (double)dt;
    if(v>best) best = v;
  }
  cout << best << '\n'; return 0;

}
