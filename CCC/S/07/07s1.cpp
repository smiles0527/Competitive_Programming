#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  const int cy = 1989, cm = 2, cd = 27;

  for(int i=0;i<n;i++){
    int y, m, d; cin >> y >> m >> d;
    
    if(y < cy) cout << "Yes\n";
    else if(y>cy) cout << "No\n";
    else{
      if(m < cm) cout << "Yes\n";
      else if(m > cm) cout << "No\n";
      else cout << (d <= cd ? "Yes\n" : "No\n");
    }

  } 
  return 0;
}
