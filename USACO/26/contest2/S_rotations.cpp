#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false); 
  cin.tie(nullptr);

  int N; cin >> N;
  vector<int> A(N+1);
  vector<char> seen(N+1,0);
  int K=0;
  for(int i=1;i<=N;i++){ cin>>A[i]; if(!seen[A[i]]) seen[A[i]]=1, K++; }

  vector<int> B(2*N+1);
  for(int i=1;i<=2*N;i++) B[i]=A[(i-1)%N+1];

  vector<int> cnt(N+1,0), R(N+1,0);
  int d=0, r=0;
  for(int l=1;l<=N;l++){
    while(d<K){
      r++;
      int x=B[r];
      if(cnt[x]++==0) d++;
    }
    R[l]=r;
    int x=B[l];
    if(--cnt[x]==0) d--;
  }

  vector<long long> best(2*N+1, (long long)4e18);

  using P = pair<long long,int>;
  priority_queue<P, vector<P>, greater<P>> hA, hB;

  for(int t=1;t<=2*N;t++){
    if(t<=N){
      int l=t, rr=R[l];
      hA.push({(long long)rr - 2LL*l, rr});
      hB.push({2LL*rr - l, rr});
    }
    while(!hA.empty() && hA.top().second < t) hA.pop();
    while(!hB.empty() && hB.top().second < t) hB.pop();
    long long a = (long long)t + hA.top().first;
    long long b = -(long long)t + hB.top().first;
    best[t] = min(a,b);
  }

  for(int j=1;j<=N;j++){
    if(j>1) cout << ' ';
    cout << min(best[j], best[j+N]);
  }
  cout << "\n";
  return 0;
}
