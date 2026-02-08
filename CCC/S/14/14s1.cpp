#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int k, m; cin >> k >> m;
  vector<int> a;
  for(int i = 0; i < k; i++){
    a.push_back(i+1);
  }
  
  for(int i = 0; i < m; i++){
    int r; cin >> r;
    vector<int> nv;
    for(int i=0; i < (int)a.size(); i++){
      if((i+1) % r != 0) nv.push_back(a[i]);
    }
    a.swap(nv);
  }
  for(int x : a) cout << x << '\n';
  return 0;
}
