#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

struct Route {
    int destination;
    ll cost;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int numIslands, numRoutes;
    cin >> numIslands >> numRoutes;
    
    vector<ll> treasure(numIslands);
    for (int i = 0; i < numIslands; i++)
        cin >> treasure[i];
    
    vector<vector<Route>> routes(numIslands);
    for (int i = 0; i < numRoutes; i++){
        int islandA, islandB;
        ll travelCost;
        cin >> islandA >> islandB >> travelCost;
        islandA--; islandB--; 
        routes[islandA].push_back({islandB, travelCost});
        routes[islandB].push_back({islandA, travelCost});
    }

    const ll NEG_INF = -1000000000000000000LL;
    vector<ll> maxProfit(numIslands, NEG_INF);
    
    priority_queue<pair<ll, int>> process;
    
    for (int i = 0; i < numIslands; i++){
        maxProfit[i] = treasure[i];
        process.push({maxProfit[i], i});
    }
    
    while (!process.empty()){
        auto [currentProfit, island] = process.top();
        process.pop();
        if (currentProfit != maxProfit[island])
            continue;  

        for (const auto &route : routes[island]){
            int nextIsland = route.destination;
            ll potentialProfit = currentProfit - route.cost;
            if (potentialProfit > maxProfit[nextIsland]){
                maxProfit[nextIsland] = potentialProfit;
                process.push({potentialProfit, nextIsland});
            }
        }
    }
    
    for (int i = 0; i < numIslands; i++){
        cout << maxProfit[i] << "\n";
    }
    
    return 0;
}
