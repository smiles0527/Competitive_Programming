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

    int n; cin >> n;
    vi P(n+1, 0);
    for(int i = 1; i <= n; i++){ ll x; cin >> x; P[i] = P[i-1] + x; }

    vi hx, hy;                                  // lower hull: points (a, P[a])
    // slope(A,B) >= slope(B,C)  =>  B not on lower hull
    auto bad = [](ll ax, ll ay, ll bx, ll by, ll cx, ll cy){
        return (by-ay)*(cx-bx) >= (cy-by)*(bx-ax);
    };

    string out; out.reserve(n*7);
    for(int i = 1; i <= n; i++){
        ll ax = i-1, ay = P[i-1];               // add candidate start a=i-1
        while(hx.size() >= 2 &&
              bad(hx[hx.size()-2], hy[hy.size()-2], hx.back(), hy.back(), ax, ay)){
            hx.pop_back(); hy.pop_back();
        }
        hx.pb(ax); hy.pb(ay);

        int lo = 0, hi = (int)hx.size()-1;       // peak of unimodal slope, leftmost on tie
        while(lo < hi){
            int m = (lo+hi)/2;
            ll n1 = P[i]-hy[m],   d1 = i-hx[m];
            ll n2 = P[i]-hy[m+1], d2 = i-hx[m+1];
            if(n1*d2 < n2*d1) lo = m+1;          // g(m) < g(m+1)
            else hi = m;
        }
        out += to_string(i - hx[lo]);
        out += (i==n ? '\n' : ' ');
    }
    cout << out;
}