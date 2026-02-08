#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int j, a; cin >> j >> a;

  auto conv = [&](char c){
    if(c == 'S') return 0;
    if(c == 'M') return 1;
    return 2;
  };
  
  vector<int> js(j+1);
  for(int i = 1; i <= j; i++){
    char c; cin >> c;
    js[i] = conv(c);
  }

  int ans = 0;
  for(int i = 0; i < a; i++){
    char nC; int num; cin >> nC >> num;
    int need = conv(nC);
    if(js[num] >= need){
      ans++;
      js[num] = -1;
    }
  }

  cout << ans << "\n";

}
