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
    int m = n*(n-1)/2;
    vi B(m);
    for(auto &x : B) cin >> x;
    sort(B.begin(), B.end());

    set<ll> tried;
    for(int c = 0; c < m; c++){
        ll v = B[c], s = B[0] + B[1] - v;        // v = a1+a2  =>  a0 = (B0+B1-v)/2
        if(s <= 0 || (s & 1)) continue;
        ll a0 = s / 2;
        if(a0 < 1 || 2*a0 > B[0]) continue;       // need a0 <= a1
        if(tried.count(a0)) continue; tried.insert(a0);

        multiset<ll> M(B.begin(), B.end());
        vi A = {a0}; bool ok = true;
        for(int t = 1; t < n && ok; t++){
            ll val = *M.begin() - a0;             // next element = min - a0
            for(ll x : A){
                auto it = M.find(val + x);
                if(it == M.end()){ ok = false; break; }
                M.erase(it);
            }
            if(ok) A.pb(val);
        }
        if(ok && M.empty()){
            for(int i = 0; i < n; i++) cout << A[i] << " \n"[i==n-1];
            return 0;
        }
    }
    return 0;
}