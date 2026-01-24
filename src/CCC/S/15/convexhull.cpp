#include <bits/stdc++.h>
using namespace std;
struct compare {
    bool operator()(vector<int> const& a, vector<int> const& b){
        if (a[0] == b[0]){
            return a[1] < b[1];
        }
        
        else{
            return a[0] > b[0];
        }
    }
};

int main(){
    int K, N, M;
    cin >> K >> N >> M;
    vector<vector<vector<int>>> graph (N + 1);
    for (int i = 0; i < M; i++){
        int a, b, t, h;
        cin >> a >> b >> t >> h;
        graph[a].push_back({t, h, b});
        graph[b].push_back({t, h, a});
        
    }
    
    int start, stop;
    cin >> start >> stop;
    
    vector<vector<int>> dist (N + 1, vector<int> (K + 1, 2147483647));
    priority_queue<vector<int>, vector<vector<int>>, compare> pq; 
    pq.push({0, K, start}); //Push start island, with 0 time and a full hull to start
    while (!pq.empty()){
        vector<int> currentEdge = pq.top(); pq.pop();
        if (currentEdge[2] == stop){
            cout << currentEdge[0];
            return 0;
        }
        for (auto seaRoute: graph[currentEdge[2]]){
            if (seaRoute[1] < currentEdge[1] && seaRoute[0] + currentEdge[0] < dist[seaRoute[2]][currentEdge[1] - seaRoute[1]]){
                dist[seaRoute[2]][currentEdge[1] - seaRoute[1]] = seaRoute[0] + currentEdge[0]; //Update distance
                pq.push({seaRoute[0] + currentEdge[0], currentEdge[1] - seaRoute[1], seaRoute[2]}); //Push next island
                
            }
            
        }
        
    }
    cout << -1;   
    return 0;
}