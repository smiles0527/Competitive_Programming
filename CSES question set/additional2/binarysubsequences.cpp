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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;

    // (a,b)=(end0,end1); append c sets that coord to a+b+1. reverse: larger -= smaller+1 (batched Euclid).
    // valid final split iff reverse reaches (0,0); minimize total subtractions = length.
    ll bestLen = LLONG_MAX, bestA = 0;
    for(ll a = 0; 2*a <= n; a++){
        ll x = a, y = n - a, len = 0; bool ok = true;
        while(x > 0 && y > 0){
            if(x == y){ ok = false; break; }            // lands on (g,g) => split unreachable
            if(x > y){ len += x/(y+1); x %= (y+1); }
            else     { len += y/(x+1); y %= (x+1); }
        }
        if(!ok) continue;
        len += x + y;                                    // trailing unary run on the surviving coord
        if(len < bestLen){ bestLen = len; bestA = a; }
    }

    // rebuild: emit bits end-to-front, then reverse
    string out;
    ll x = bestA, y = n - bestA;
    while(x > 0 && y > 0){
        if(x > y){ ll k = x/(y+1); out.append((size_t)k, '0'); x %= (y+1); }
        else     { ll k = y/(x+1); out.append((size_t)k, '1'); y %= (x+1); }
    }
    if(x > 0) out.append((size_t)x, '0');
    else if(y > 0) out.append((size_t)y, '1');
    reverse(out.begin(), out.end());

    cout << out << "\n";
}