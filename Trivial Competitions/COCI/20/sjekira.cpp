#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int n;
int t[MAXN];
vector<pair<int,int>> edges;
int uf[MAXN], mv[MAXN];
ll sol = 0;

int find_root(int x) {
    return uf[x] == x ? x : uf[x] = find_root(uf[x]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> t[i];
        uf[i] = i;
        mv[i] = t[i];
    }

    for(int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u-1, v-1);
    }

    sort(edges.begin(), edges.end(),
         [&](const pair<int,int>& a, const pair<int,int>& b){
             int xa = max(t[a.first], t[a.second]);
             int xb = max(t[b.first], t[b.second]);
             return xa < xb;
         }
    );

    for(auto &e : edges){
        int x = e.first, y = e.second;
        int rx = find_root(x);
        int ry = find_root(y);
        if(rx != ry){
            sol += mv[rx] + mv[ry];
            uf[rx] = ry;
            mv[ry] = max(mv[ry], mv[rx]);
        }
    }

    cout << sol << "\n";
    return 0;
}
