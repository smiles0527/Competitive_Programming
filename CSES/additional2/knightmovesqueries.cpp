#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;

ll knight(ll a, ll b){                       // dist from (0,0) to (a,b), a,b>=0, quarter-plane (coords stay >=0)
    if(a < b) swap(a, b);
    if(a == 1 && b == 0) return 3;           // exceptions vs base formula, found by BFS diff
    if(a == 1 && b == 1) return 4;
    if(a == 2 && b == 2) return 4;
    ll d = max((a + 1) / 2, (a + b + 2) / 3);
    d += (d - (a + b)) & 1;                  // parity: d ≡ a+b (mod 2)
    return d;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q; cin >> q;
    string out; out.reserve(q * 7);
    while(q--){
        ll x, y; cin >> x >> y;
        out += to_string(knight(x - 1, y - 1));
        out += '\n';
    }
    cout << out;
}