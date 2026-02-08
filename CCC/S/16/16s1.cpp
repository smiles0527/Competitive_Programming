#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a, b; cin >> a >> b;
  
  vector<int> cnt(26);
  for(char c : a) cnt[c - 'a']++;

  for(char c : b){
    if(c != '*'){
      if(cnt[c-'a'] == 0){
        cout << "N";
        return 0;
      }
      cnt[c-'a']--;
    }
  }
  cout << "A";
}
