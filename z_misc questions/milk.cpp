#include <bits/stdc++.h>
using namespace std;
using ll long long;


int64 floor_sum(int64 n, int64 m, int64 a, int64 b){
  int64 ans = 0;
  while(true){
    if(a>=m){
      ans += (n-1)*n/2*(a/m); a %= m;
    } 
    if(b>=m){
      ans+=n*(b/m);b%=m;
    }
    int64 y = a*n+b;
    if(y<m)break; n = y/m; b=y%m; swap(a, m);
  }
  return ans;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N; int64 D; cin >> N >> D;

  const int64 LIM = 10000000LL; int64 total = 0;
  for(int i = 0; i < N; i++){
    int64 A, B, C; cin >> A >> B >> C;
    
    int64 a = ((A%C) + C) % C;
    int64 b = ((A+B)%C + C) % C;
    int64 n = D;
    int64 x;
    if(n%2==0) x = (n/2)*(n-1); else x = n*((n-1)/2);

    int64 linear = ((a%c)*(x%c)+(b%C)*(n%C))%C;
    int64 fs = floor_sum(n, C, a, b); int64 ms = linear - (fs % C) * C;

    total += ms;
  }

  cout << total / LIM << '\n';
}
