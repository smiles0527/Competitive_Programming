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

int N;
vi bit;                                  // count of present positions
void upd(int i, ll v){ for(; i <= N; i += i & -i) bit[i] += v; }
ll qry(int i){ ll r = 0; for(; i; i -= i & -i) r += bit[i]; return r; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    N = n;
    bit.assign(n+1, 0);
    vii v(n);                            // (value, position)
    for(int i = 1; i <= n; i++){ cin >> v[i-1].f; v[i-1].s = i; upd(i, 1); }

    sort(v.begin(), v.end());            // process smallest value first

    ll ans = 0;
    int present = n;
    for(auto &e : v){
        int p = e.s;
        ll L = qry(p-1);                 // present elements left of p
        ll R = (present - 1) - L;        // present elements right of p
        ans += min(L, R);                // slide to nearer end
        upd(p, -1); present--;           // freeze this element
    }
    cout << ans << '\n';
}