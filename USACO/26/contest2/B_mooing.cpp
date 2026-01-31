#include <bits/stdc++.h>
using namespace std;

void solve(){
  int T, K; cin >> T >> K;

  while(T--){
    int N; string S; cin >> N >> S;

    cout << "YES\n";

    if(K){
      string K = S;
      int flip = 0;
      for(int i = N - 1; i >= 0; --i){
        char c = S[i];
        if(flip) c = (c == 'M' ? 'O' : 'M');
        K[i] = c;
        if(c == 'O') flip ^= 1;
      }

      cout << K << '\n';
    }

  }

}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;

}
