#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t, n; cin >> t >> n;
  vector<int> d(n), p(n);
  for(int &x : d) cin >> x;
  for(int &x : p) cin >> x;

  sort(d.begin(), d.end());
  sort(p.begin(), p.end());

  long long ans = 0;
  if(t==1) for(int i = 0; i < n; i++) ans += max(d[i], p[i]);
  else for(int i = 0; i < n; i++) ans += max(d[i], p[n-1-i]);
  
  cout << ans << '\n';
}
