#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int j; cin >> j;
  int n = j - 1;

  if(n < 3){
    cout << 0 << '\n'; return 0;
  }

  cout << n * (n-1) * (n-2) / 6 << '\n'; 
  return 0;
}
