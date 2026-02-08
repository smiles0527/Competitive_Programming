#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long a, b; cin >> a >> b;
  int cnt = 0;
  
  int i = 0;
  while(pow(i, 6) <= b){
    if(pow(i, 6) >= a) cnt++; 
    i++;
  }

  cout << cnt << '\n'; return 0;
}
