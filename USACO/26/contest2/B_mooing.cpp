#include <bits/stdc++.h>
using namespace std;
/*
  Key observations:
  - Typing M just appends M 
  - Typig O flips the entire current string (M <--> O), then appends O 
  - The last character of the final string always equals the last keystroke

  This means we construct the keystrokes backwards

  So our strategy should be to work from the end of the target string S to the front.

  We can maintain a boolean flip (0/1)
  - if flip = 0, characters are normal
  - if flip = 1, characters are logically flipped

  At position i (from right to left):
  1. Let c be S[i], flipped if flip == 1
  2. That c must be the keystroke at position i 
  3. If c == 'O', toggling noccurs when removing it --> flip 

  This always succeeds (answer is always YES)

  Timme complexity: O(N) per test case
  Space complexity: O(N) if constructing the keystrokes



  */
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
