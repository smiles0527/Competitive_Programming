#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  vector<int> a(n); for(auto &x : a) cin >> x;
  
  int x;
  while(cin >> x && x != 77){
    if(x == 99){
      int k; double p; cin >> k >> p; k--;
      double v = a[k];
      double L = v * (p/100.0), R = v - L;
      a[k] = L;
      a.insert(a.begin()+k+1, R);
    }else{
      int k; cin >> k; k--;
      a[k] += a[k+1];
      a.erase(a.begin()+k+1);
    }
  }
  for(int i = 0; i < (int)a.size(); i++){
    long long v = llround(a[i]);
    if(i) cout << ' '; cout << v;
  }
  cout << '\n';
  return 0;
}
