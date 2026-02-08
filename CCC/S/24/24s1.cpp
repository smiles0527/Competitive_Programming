#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n; cin >> n;
  vector<int> a(n); for(int &x : a) cin >> x;

  int x = n/2; long long ans = 0;
  for(int i = 0; i < n; i++) {if(a[i] == a[(i+x)%n]) ans++;}
  cout << ans << '\n';
}
