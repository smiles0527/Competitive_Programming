#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,k; 
  cin >> n >> k;
  vector<int> v(n);
  for(int i=0;i<n;i++) cin >> v[i];

  vector<int> srt=v;
  sort(srt.begin(), srt.end());

  unordered_map<int,int> gid;
  gid.reserve((size_t)n*2+1);
  gid.max_load_factor(0.7f);
  for(int i=0;i<n;i++) gid[srt[i]] = i / k;

  vector<int> d; 
  d.reserve(n);
  for(int x: v){
    int g = gid[x];
    auto it = upper_bound(d.begin(), d.end(), g);
    if(it==d.end()) d.push_back(g);
    else *it = g;
  }

  cout << (n - (int)d.size()) << "\n";
}
