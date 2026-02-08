#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int w, n; cin >> w >> n;
  vector<int> a(n); for(auto &x : a) cin >> x;

  queue<int> q; int sum = 0; int passed = 0;

  for(int i=0;i<n;i++){
    q.push(a[i]); sum += a[i];

    if((int)q.size() > 4){ sum -= q.front(); q.pop(); }
    if(sum > w) break; 
    passed++;
  }
  cout << passed << '\n';
}
