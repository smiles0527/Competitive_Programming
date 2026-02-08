#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  string input; cin >> input;
  int h = 0, v = 0;
  for(char c : input){
    if(c == 'H') h ^= 1;
    else v ^= 1;
  }
  if(h == 0 && v == 0) cout << "1 2\n3 4\n";
  else if(h==1 && v == 0) cout << "3 4\n1 2\n";
  else if(h == 0 && v == 1) cout << "2 1\n4 3\n";
  else cout << "4 3\n2 1\n";
}
