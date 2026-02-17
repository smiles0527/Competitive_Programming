#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string c, ans;
  int t, mn = 1e9;

  while(cin >> c >> t){
    if(t < mn){ mn = t; ans = c; } 
    if(c == "Waterloo") break;
  }
  cout << ans << '\n';
  return 0;
}
