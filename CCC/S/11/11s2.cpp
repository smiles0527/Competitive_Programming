#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  vector<char> a(n); for(auto &x : a) cin >> x;
  
  int cnt = 0;
  for(int i=0;i<n;i++){
    char c; cin >> c;
    if(c == a[i]) cnt++;
  }
  cout << cnt << '\n';
}
