#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<int>> c(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> c[i][0] >> c[i][1];  
        c[i][2] = i;                
    }
    
    sort(c.begin(), c.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] < b[0];
    });

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> assign(n);
    int roomCount = 0;

    for(int i = 0; i < n; i++){
        int arrive = c[i][0];
        int depart = c[i][1];
        int idx = c[i][2];

        if(!pq.empty() && pq.top().first < arrive){
            int roomNo = pq.top().second;
            pq.pop();
            assign[idx] = roomNo;
            pq.push({depart, roomNo});
        } else {
            roomCount++;
            assign[idx] = roomCount;
            pq.push({depart, roomCount});
        }
    }
    cout << roomCount << "\n";
    for (int i = 0; i < n; i++) {
        cout << assign[i] << (i+1 < n ? ' ' : '\n');
    }
    return 0;

}