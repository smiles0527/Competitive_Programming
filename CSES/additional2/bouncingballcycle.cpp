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

ll cnt(ll a, ll P, ll r){ return r <= a ? (a - r) / P + 1 : 0; }   // #x in [0,a], x≡r (mod P)

// |A|: R≡C (mod P)
ll cntEq(ll a, ll b, ll P){
    ll Qa = a / P, ba = a % P, Qb = b / P, bb = b % P;
    ll m1 = min(ba, bb), m2 = max(ba, bb);
    ll res = (m1 + 1) * (Qa + 1) * (Qb + 1);
    if(ba < bb) res += (m2 - m1) * (Qa * (Qb + 1));
    else        res += (m2 - m1) * ((Qa + 1) * Qb);     // ba==bb => zero-width
    res += (P - 1 - m2) * (Qa * Qb);
    return res;
}

// |B|: R≡-C (mod P)   (w(ρ)=v(-ρ): hits Qb+1 at ρ=0 and ρ∈[P-bb,P-1])
ll cntOpp(ll a, ll b, ll P){
    ll Qa = a / P, ba = a % P, Qb = b / P, bb = b % P;
    ll N = 1 + max(0LL, ba + bb - P + 1);               // overlap of {ρ≤ba} with {0}∪[P-bb,P-1]
    return P * Qa * Qb + Qa * (bb + 1) + Qb * (ba + 1) + N;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        ll n, m; cin >> n >> m;
        ll a = n - 1, b = m - 1, g = __gcd(a, b), P = 2 * g;
        ll steps = 2 * a / g * b;                        // lcm(2a,2b) = 2ab/g
        ll AB = cnt(a, P, 0) * cnt(b, P, 0) + cnt(a, P, g) * cnt(b, P, g);   // A∩B: both ≡0 or both ≡g (mod 2g)
        ll vis = cntEq(a, b, P) + cntOpp(a, b, P) - AB;
        cout << steps << ' ' << vis << "\n";
    }
}