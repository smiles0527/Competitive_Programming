#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n; cin >> n;
  unordered_map<string, char> map;
  for(int i = 0; i < n; i++){
    char c; string str; cin >> c >> str;  
    map[str] = c;
  }
  string s, cur; cin >> s;  

  for(char b : s){
    cur += b;
    if(map.count(cur)){
      cout << map[cur];
      cur.clear();
    }
  }
  cout << '\n';
}
