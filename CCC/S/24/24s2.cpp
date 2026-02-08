#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t, n; cin >> t >> n;

  unordered_map<char, int> map;
  for(int i = 0; i < t; i++){
    string s; cin >> s; for(char c : s) map[c]++;
    for(int j = 0; j < n; j++){
      if(map[s[j]] > 1 && map[s[j+1]] > 1 || (map[s[j]] == 1 && map[s[j+1]] == 1)){
        cout << "F\n"; break;
      }
      else if (j == n -1) cout << "T\n";
    }
    map.clear();
  }
}
