#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q, a, b, c; cin >> q >> a >> b >> c;
  int p = 0, t = 0;

  while(q--){
    t++;

    if(p==0){
      if(++a % 35 == 0) q += 30;
    } else if(p==1){
      if(++b % 100 == 0) q += 60;
    } else{
      if(++c % 10 == 0) q += 9;
    }

    p = (p+1)%3; if(q < 0) break;
  }

  cout << "Martha plays " << t << " times before going broke.\n";
  return 0;
}
