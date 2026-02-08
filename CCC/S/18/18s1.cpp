#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  vector<int> p(n);
  for(int &i : p) cin >> i; sort(p.begin(), p.end());
  
  double best = 1e100;
  for(int i = 1; i <= n-2; i++){
      double size = (p[i+1]-p[i-1]) / 2.0;
      if(size < best) best = size;
  }

  cout << fixed << setprecision(1) << best << '\n'; return 0;
}
