#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int N; cin >> N;
  vector<int> a(N+1);
  for(int i = 2; i <= N; i++) if(!a[i]){
    a[i] = i;
    if(1LL * i * i <= N){
      for(long long j = 1LL * i * i; j <= N; j+=i){
        if(!a[(int) j])
          a[(int) j] = i;
      }
    }
  }

  long long ans = 0;
  for(int x = N; x > 1; ){
    int p = a[x];
    ans += p - 1;
    x -= x / p;
  }

  cout << ans; return 0;
}
