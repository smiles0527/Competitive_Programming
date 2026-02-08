#include <bits/stdc++.h>
using namespace std;

vector<int> g[26];
int vis[26];
int low[26];
int previ[26];
int start[26];
int fin[26];
int cur = 0;

vector<string> disc;
map<pair<int,int>, string> name;

int B = 1;
    
void dfs(int u){
    cur++;
    vis[u] = low[u] = cur;
    start[u] = cur;

    for (int v : g[u]){
        if (!vis[v]){
            previ[v] = u;
            dfs(v);

            low[u] = min(low[u], low[v]);

            if (low[v] > vis[u]){
                if (start[v] <= start[B] && start[B] <= fin[v]){
                    disc.push_back(name[{min(u,v), max(u,v)}]);
                }
            }
        }

        else if (v != previ[u]){
            low[u] = min(low[u], vis[v]);
        }
    }

    fin[u] = cur;

}

int main(){
    string str;

    while (cin >> str && str != "**"){
        int u = str[0] - 'A';
        int v = str[1] - 'A';

        g[u].push_back(v);
        g[v].push_back(u);

        name[{min(u,v), max(u,v)}] = str;
    }

    dfs(0);

    sort(disc.begin(), disc.end());

    for (auto smth : disc){
        cout << smth << "\n";
    }

    cout << "There are " << disc.size() << " disconnecting roads.\n";
}
