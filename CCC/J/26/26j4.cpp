#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int m; cin >> m;
    vector<string> a(m); for(auto &x : a) cin >> x;
    set<pair<int, int>> slimy;
    int x = 0, y = 0;
    slimy.insert({x, y});

    ll ans = 0;
    for(int i = 0; i < m; i++){
        string s = a[i];

        char dir = s[0];
        int d = stoi(s.substr(1));

        int dx = 0, dy = 0;
        if(dir == 'N') dy = -1;
        if(dir == 'S') dy = 1;
        if(dir == 'E') dx = 1;
        if(dir == 'W') dx = -1;

        while(d--){
            x += dx;
            y += dy;
            if(slimy.count({x, y})){
                ans++;
            }
            slimy.insert({x, y});
        }
    }
    cout << ans << '\n';
}