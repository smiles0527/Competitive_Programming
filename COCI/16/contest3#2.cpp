#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<string> G(N);
    for(int i = 0; i < N; i++) {
        cin >> G[i];
    }

    string answer;
    answer.reserve(N + M - 1);
    answer.push_back(G[0][0]);

    vector<pair<int,int>> cur;
    cur.emplace_back(0, 0);

    vector<vector<int>> seen(N, vector<int>(M, 0));
    int marker = 1;

    // total moves = N+M-2
    for(int step = 1; step < N + M - 1; step++){
        char best = 'z' + 1;
        // collect candidates
        vector<pair<int,int>> cand;
        cand.reserve(cur.size()*2);

        for(auto &p : cur){
            int r = p.first, c = p.second;
            if(r + 1 < N){
                char ch = G[r+1][c];
                if(ch < best) best = ch;
            }
            if(c + 1 < M){
                char ch = G[r][c+1];
                if(ch < best) best = ch;
            }
        }

        marker++;
        vector<pair<int,int>> next;
        next.reserve(cur.size()*2);

        for(auto &p : cur){
            int r = p.first, c = p.second;
            if(r + 1 < N && G[r+1][c] == best && seen[r+1][c] != marker){
                seen[r+1][c] = marker;
                next.emplace_back(r+1, c);
            }
            if(c + 1 < M && G[r][c+1] == best && seen[r][c+1] != marker){
                seen[r][c+1] = marker;
                next.emplace_back(r, c+1);
            }
        }

        answer.push_back(best);
        cur.swap(next);
    }

    cout << answer << "\n";
    return 0;
}
