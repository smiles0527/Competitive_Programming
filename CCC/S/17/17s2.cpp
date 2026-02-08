#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n; cin >> n;
  vector<int> v(n); for(auto &x : v) cin >> x;
  sort(v.begin(), v.end());

  int mid = (n - 1)/2; int hi = mid + 1;

  for(int lo = mid; lo >= 0; lo--){
    cout << v[lo];
    if(hi < n) cout << ' ' << v[hi++];
    if(lo != 0 || hi < n) cout << ' ';
  }
  cout << '\n';
}
