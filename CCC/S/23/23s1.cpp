#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  vector<int> a(n), b(n);
  for(int &x : a) cin >> x; 
  for(int &x : b) cin >> x;

  int ans = 0;
  for(int i = 0; i < n; i++){ 
    if(a[i]) ans += 3;
    if(b[i]) ans += 3;
  }

  for(int i = 0; i+1 < n; i++){
    if(a[i] && a[i+1]) ans -= 2;
    if(b[i] && b[i+1]) ans -= 2;
  }

  for(int i = 0; i < n; i++){
    if(a[i] && b[i] && i%2==0) ans -= 2;
  }

  cout << ans << '\n';
}
