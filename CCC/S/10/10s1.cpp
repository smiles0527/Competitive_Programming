#include <bits/stdc++.h>
using namespace std;

struct C{ string n; long long s; };

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int k; cin >> k;
  vector<C> v; v.reserve(k);

  for(int i = 0; i <  k; i++){
    string n; int r, c, d; 
    cin >> n >> r >> c >> d;

    long long s = 2*r+3*c+d;
    v.push_back({n, s});
  }

  sort(v.begin(), v.end(), [](const C& a, const C& b){
    if(a.s != b.s) return a.s > b.s;
    return a.n < b.n;
  });
  
  if(v.empty()) return 0;
  cout << v[0].n << '\n';
  if(k>=2) cout << v[1].n << '\n';
  return 0;
}
