#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        int n, m, k; cin >> n >> m >> k;
        vector<int> robots(n), spikes(m); 
        for(int i = 0; i < n; i++) cin >> robots[i];
        for(int i = 0; i < m; i++) cin >> spikes[i];

        string tasks; cin >> tasks;
        sort(spikes.begin(), spikes.end()); 

        unordered_set<long long> alive;
        for(int i = 0; i < n; i++) alive.insert(robots[i]); 


        
        long long loc = 0;

        for(int i = 0; i < (int)tasks.length(); i++){
            if(tasks[i] ==  'L') loc--;
            else loc++;

            vector<long long> dead;
            for(long long x : alive) {if(x == loc) dead.push_back(x);
            for(long long x : dead) alive.erase(x);

            cout << alive.size() << (i + 1 == k ? "\n" : " ");
        }
    }

    return 0;
}