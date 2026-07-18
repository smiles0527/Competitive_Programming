#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;

int fav, g;
int pts[5];
vector<pair<int,int>> rem;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> fav >> g;

    set<pair<int,int>> played;
    for (int i = 0; i < g; i++) {
        int a, b, sa, sb; cin >> a >> b >> sa >> sb;
        played.insert({a, b});
        played.insert({b, a});
        if (sa > sb) pts[a] += 3;
        else if (sa < sb) pts[b] += 3;
        else { pts[a] += 1; pts[b] += 1; }
    }

    int pairs[6][2] = {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}};
    for (auto& pr : pairs)
        if (!played.count({pr[0], pr[1]}))
            rem.push_back({pr[0], pr[1]});

    int r = rem.size();
    int total = 1;
    for (int i = 0; i < r; i++) total *= 3;

    int ans = 0;
    for (int mask = 0; mask < total; mask++) {
        int cur[5];
        for (int t = 1; t <= 4; t++) cur[t] = pts[t];
        int m = mask;
        for (int i = 0; i < r; i++) {
            int o = m % 3; m /= 3;
            int a = rem[i].first, b = rem[i].second;
            if (o == 0) cur[a] += 3;        // a wins
            else if (o == 1) cur[b] += 3;   // b wins
            else { cur[a] += 1; cur[b] += 1; }  // tie
        }
        bool champ = true;
        for (int t = 1; t <= 4; t++)
            if (t != fav && cur[t] >= cur[fav]) { champ = false; break; }
        if (champ) ans++;
    }

    cout << ans << '\n';
    return 0;
}