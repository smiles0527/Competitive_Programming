#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  unordered_map<char, int> val{
    {'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}
  };

  string s; cin >> s;
  int total = 0;

  for(int i=0;i<s.size();i+=2){
    int cur = (s[i] - '0') * val[s[i+1]];

    if(i+2 < s.size() && val[s[i+3]] > val[s[i+1]])
      total -= cur;
    else
      total += cur;
  }
  cout << total << '\n';
}
