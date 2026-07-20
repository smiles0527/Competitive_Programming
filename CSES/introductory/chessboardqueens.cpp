#include <bits/stdc++.h>
using namespace std;
char g[8][9];
bool col[8], d1[15], d2[15];        // d1: r+c, d2: r-c+7
int ans = 0;

void solve(int r){
    if(r==8){ ans++; return; }
    for(int c=0;c<8;c++){
        if(g[r][c]=='*' || col[c] || d1[r+c] || d2[r-c+7]) continue;
        col[c]=d1[r+c]=d2[r-c+7]=1;
        solve(r+1);
        col[c]=d1[r+c]=d2[r-c+7]=0;
    }
}

int main(){
    for(int i=0;i<8;i++) cin >> g[i];
    solve(0);
    cout << ans << "\n";
}
