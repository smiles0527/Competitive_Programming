#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

class path{
public:
    int x, y, length;
};

int n, m;
const int maxn = 1001;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
char grid[maxn][maxn];
int dist[maxn][maxn];
char dc[4] = {'D', 'U', 'R', 'L'};

int startx, starty, endx, endy;
bool not_valid(int x, int y){
        if(grid[x][y] == '#') return true;
        if(x < 0) return true;
        if(y < 0) return true;
        if(x >= n) return true;
        if(y >= m) return true;
        return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'A'){
                startx = i;
                starty = j;
            } 
            if(grid[i][j] == 'B'){
                endx = i;
                endy = j;
            }
        }
    }    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            dist[i][j] = -1;
        }
    }
    
    queue<path> bfs;
    bfs.push({startx, starty, 0});
    while(!bfs.empty()){
        path p = bfs.front();  
        bfs.pop();

        if(not_valid(p.x, p.y)) continue;
        if(dist[p.x][p.y] != -1) continue;
        dist[p.x][p.y] = p.length;

        for(int i = 0; i < 4; i++){
            bfs.push({p.x + dx[i], p.y + dy[i], p.length + 1});
        }
    }
    if(dist[endx][endy] == -1){
        cout << "NO\n";
        return 0;
    }

    string str = "";
    int cx = endx, cy = endy;
    while(cx != startx || cy != starty){
        for(int i = 0; i < 4; i++){
            if(!not_valid(cx - dx[i], cy - dy[i])){
                if(dist[cx][cy] == dist[cx - dx[i]][cy - dy[i]] + 1){
                    str += dc[i];
                    cx -= dx[i];
                    cy -= dy[i];
                    break;
                }
            }
        }
    }
    reverse(str.begin(), str.end());
    cout << "YES\n" << dist[endx][endy] << "\n" << str << "\n";

}