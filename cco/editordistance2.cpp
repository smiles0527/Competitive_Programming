#include <iostream>
#include <algorithm>
#include <set> 
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n; 
    cin >> n;

    vector<int> numberCharacters(n);
    for(int i = 0; i < n; i++) cin >> numberCharacters[i];

    int rs, cs, rf, cf;
    cin >> rs >> cs >> rf >> cf;
    rs--; cs--; rf--; cf--;

    queue<pair<int, int>> q;
    q.push({rs, cs});
    vector<vector<bool>> visited(n);

    for(int i = 0; i < n; i++) visited[i].resize(numberCharacters[i], false);
    visited[rs][cs] = true;

    int len = 0;
    //RLDU

    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto[r, c] = q.front();
            q.pop();
            if(r == rf && c == cf){
                cout << len << '\n';
                return 0;
            }

            //R
            if(c + 1 < numberCharacters[r] && !visited[r][c+1]){
                visited[r][c+1] = true; 
                q.push({r, c+1});
            } else if(c + 1 == numberCharacters[r] && r + 1 < n && !visited[r+1][0]){
                visited[r+1][0] = true;
                q.push({r + 1, 0});
            }

            //L
            if(c - 1 >=0 && !visited[r][c-1]){
                visited[r][c-1] = true; 
                q.push({r, c-1});
            } else if(c == 0 && r - 1 >= 0 && !visited[r-1][numberCharacters[r-1]-1]){
                visited[r-1][numberCharacters[r-1]-1] = true;
                q.push({r - 1, numberCharacters[r-1]-1});
            }
            
            //U
            if(r - 1 >= 0){
                int dc = c < numberCharacters[r-1] ? c : numberCharacters[r-1] - 1;
                if(!visited[r-1][dc]){
                    visited[r-1][dc] = true;
                    q.push({r-1, dc});
                }
            } 

            //D
            if(r + 1 < n){
                int dc = c < numberCharacters[r+1] ? c : numberCharacters[r+1] - 1;
                if(!visited[r+1][dc]){
                    visited[r+1][dc] = true;
                    q.push({r+1, dc});
                }
            }

            
        }
        len++;  
    }
}