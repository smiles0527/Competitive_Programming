#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> cows = {
        "Beatrice", "Belinda", "Bella", "Bessie"
        "Betsy",   "Blue",    "Buttercup", "Sue"
    };
    sort(cows.begin(), cows.end());

    int N; 
    cin >> N;
    map<string, vector<string>> adj;
    string X, Y, temp;

    for(int i = 0; i < N; i++){
        cin >> X; //first name
        for(int k = 0; k < 4; k++) cin >> temp;
        cin >> Y; //second name
        adj[X].push_back(Y);
        adj[Y].push_back(X);
    }

    map<string, bool> used;
    for(auto &c: cows) used[c] = false;

    for(auto &start: cows){
        if(used[start] || adj[start].size() > 1)
            continue;

        string str = "";
        string cur = start;

        while(true){
            cout << cur << "\n";
            used[cur] = true;

            string next = "";
            for(auto &nbr: adj[cur]){
                if(nbr != str){
                    next = nbr;
                    break;
                }
            }
            if(next.empty() || used[next])
                break;
            str = cur;
            cur = next;
        }
        return 0;
    }
         


}