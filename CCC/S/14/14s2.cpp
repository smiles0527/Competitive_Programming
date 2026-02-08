#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n; cin >> n;
  vector<string> a(n), b(n);
  for(auto &x : a) cin >> x;
  for(auto &x : b) cin >> x;

  unordered_map<string, string> p; p.reserve(n*2);
  for(int i = 0; i < n; i++) p[a[i]] = b[i];
  for(int i = 0; i < n; i++){
    if(a[i] == p[a[i]]) { cout << "bad\n"; return 0;}
    if(!p.count(p[a[i]]) || p[p[a[i]]] != a[i]) { cout << "bad\n"; return 0;}
  }

  cout << "good\n";
}
