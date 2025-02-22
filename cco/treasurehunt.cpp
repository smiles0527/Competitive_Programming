//Day 1, Problem 1:Treasure Hunt
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
        }
    }
    int x = 0, y = 0;
    while(x < n && y < m){
        if(grid[x][y] == 'N'){
            x--;
        }
    }
    cout << x << " " << y << endl;
}