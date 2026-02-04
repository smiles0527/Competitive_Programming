#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin>>n;
  vector<int> A(n);
  for(int i=0;i<n;i++) cin>>A[i];

  int m; cin>>m;
  vector<int> B(m);
  for(int i=0;i<m;i++) cin>>B[i];

  unordered_map<int,int> pos;
  pos.reserve((size_t)m*2+1);
  pos.max_load_factor(0.7f);
  for(int i=0;i<m;i++) pos[B[i]]=i;

  vector<int> dp; dp.reserve(min(n,m));
  for(int x:A){
    auto it=pos.find(x);
    if(it==pos.end()) continue;
    int p=it->second;
    auto jt=lower_bound(dp.begin(),dp.end(),p);
    if(jt==dp.end()) dp.push_back(p);
    else *jt=p;
  }

  cout<<dp.size()<<"\n";
}
