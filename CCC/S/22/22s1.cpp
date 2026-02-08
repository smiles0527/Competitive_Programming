#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long N; cin >> N;
  int cnt = 0;

  while(N >= 0){
    if(N % 5 ==0) cnt++; N -= 4;
  }
  cout << cnt;
}
