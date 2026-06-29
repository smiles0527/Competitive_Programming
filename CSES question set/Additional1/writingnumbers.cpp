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
typedef __int128 lll;
const ll MOD = 1e9 + 7;

// occurrences of digit d in 1..N
lll cntD(ll N, int d){
    lll res = 0;
    for(lll p = 1; p <= N; p *= 10){
        lll high = N / (p*10), cur = (N / p) % 10, low = N % p;
        if(d > 0){
            if(cur > d)      res += (high+1)*p;
            else if(cur == d)res += high*p + low + 1;
            else             res += high*p;
        } else {                                   // d == 0, no leading zeros
            if(cur > 0)      res += high*p;
            else             res += (high-1)*p + low + 1;
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;

    auto ok = [&](ll N){                            // all digits within budget
        for(int d = 0; d < 10; d++) if(cntD(N, d) > (lll)n) return false;
        return true;
    };

    ll lo = 1, hi = (ll)2e18;
    while(lo < hi){
        ll md = lo + (hi - lo + 1)/2;
        if(ok(md)) lo = md; else hi = md - 1;
    }
    cout << lo << '\n';
}