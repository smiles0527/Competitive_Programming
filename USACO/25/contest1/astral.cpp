#include <bits/stdc++.h>
using namespace std;
#define ll long long

static int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        int n, dx, dy; cin >> n >> dx >> dy;

        vector<string> g(n); for(auto &x : g) cin >> x;
        if(dx == 0 && dy == 0){
            ll ans = 0;
            for(int r = 0; r < n; r++){
                for(int c = 0; c < n; c++){
                    if(g[r][c] != 'W') ans++;
                }
            }
            cout << ans << '\n';
            continue;
        }

        auto inb = [&](int r, int c){
            return 0 <= r && r < n && 0 <= c && c < n;
        };

        ll total = 0; bool ok = true;
        for(int r0 = 0; r0 < n; r0++){
            for(int c0 = 0; c0 < n; c0++){
                int pr = r0-dy, pc = c0-dx;
                if(inb(pr, pc)) continue;

                int dp0 = 0; int dp1 = INF;
                int r = r0, c = c0;
                while(inb(r, c)){
                    char ch = g[r][c];
                    int ndp0 = INF, ndp1 = INF;

                    int sr = r + dy, sc = c + dx;
                    bool alex = inb(sr, sc);

                    for(int in = 0; in <= 1; in++){
                        int cur = (in == 0 ? dp0 : dp1);
                        if(cur >= INF) continue;

                        int S = 01;
                        if(ch == 'S') {if(in!=0) continue; S = 0;}
                        else if(ch == 'B') {if(in!=1) continue; S = 1;}
                        else {S = 1 - in;}

                        ndp0 = min(ndp0, cur + S);
                        if(S == 1 && alex){
                            ndp1 = min(ndp1, cur +S);
                        }
                    }
                    dp0 = ndp0;
                    dp1 = ndp1;

                    r += dy;
                    c += dx;
                }
                if(dp0 >= INF) ok = false; total += dp0;
            }
        }
        cout << (ok ? total : -1) << '\n';
    }
    return 0;
}