#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string start = "";
    for(int i = 0; i < 9; i++){
        char c; cin >> c;
        start += c;
    }

    string target = "123456789";
    vector<pair<int, int>> edges;

    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            int id = 3 * r + c;
            
            if(r+1<3) edges.pb({id, id+3});
            if(c+1<3) edges.pb({id, id+1});
        }
    }

    queue<string> q;
    unordered_map<string, int> dist;

    q.push(start);
    dist[start] = 0;

    while(!q.empty()){
        string cur = q.front(); q.pop();

        if(cur==target){
            cout << dist[cur] << '\n';
            return 0;
        }

        for(auto e : edges){
            string nxt = cur;
            swap(nxt[e.f], nxt[e.s]);

            if(!dist.count(nxt)){
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    return 0;
}