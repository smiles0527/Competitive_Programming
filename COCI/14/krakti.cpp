#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long n,k;
  cin >> n >> k;

  if(k<1 || k>n || n>k*k || (k==1 && n>1)){
    cout << -1 << "\n";
    return 0;
  }

  vector<int> ans;
  ans.reserve((int)n);

  for(long long i=n;i>=1;i-=k){
    long long l=max(1LL, i-k+1);
    for(long long j=l;j<=i;j++) ans.push_back((int)j);
  }

  for(int i=0;i<(int)ans.size();i++){
    if(i) cout << ' ';
    cout << ans[i];
  }
  cout << "\n";
}
