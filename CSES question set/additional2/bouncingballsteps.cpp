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

ll fold(ll k, ll L){            // L = dimension; triangular wave on [1,L], period 2(L-1)
    ll P = 2*(L-1), t = k % P;
    return t <= L-1 ? 1+t : 1+(P-t);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        ll n, m, k; cin >> n >> m >> k;
        ll r = fold(k, n), c = fold(k, m);
        ll a = n-1, b = m-1, g = __gcd(a, b), l = a/g*b;     // lcm(n-1,m-1) <= 1e18
        ll ch = k/a + k/b - k/l;                             // corner = simultaneous flip, counted once
        cout << r << ' ' << c << ' ' << ch << "\n";
    }
}