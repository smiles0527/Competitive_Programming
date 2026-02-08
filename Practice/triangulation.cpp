#include <bits/stdc++.h>
using namespace std;

long long triangulations(int n){
  if(n<3) return 0;
  int m = n - 2;
  vector<long long> C(m+1,0); C[0] = 1;

  for(int i = 1; i <= m; i++){
    for(int j = 0; j < i; j++){
      C[i] += C[j] * C[i-1-j];
    }
  }
  return C[m];
}
