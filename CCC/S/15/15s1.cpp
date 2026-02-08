#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int k; cin >> k;
  vector<int> a;
  while(k--){
    int n; cin >> n;
    if(n == 0) a.pop_back();  
    else a.push_back(n);
  }

  int sum = 0; for(auto &x : a) sum+=x; cout << sum;
}
