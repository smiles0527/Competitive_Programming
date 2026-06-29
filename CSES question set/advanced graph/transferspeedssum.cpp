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

int p[200005], sz[200005];
int fnd(int x){ while(x != p[x]) x = p[x] = p[p[x]]; return x; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<array<int,3>> e(n - 1);           // (w, a, b)
    for(int i = 0; i < n - 1; i++){
        int a, b, x; cin >> a >> b >> x;
        e[i] = {x, a, b};
    }
    sort(e.begin(), e.end(), greater<array<int,3>>());   // heavy -> light
    for(int i = 1; i <= n; i++){ p[i] = i; sz[i] = 1; }

    ll ans = 0;
    for(auto &ed : e){
        int w = ed[0], a = fnd(ed[1]), b = fnd(ed[2]);
        ans += (ll)w * sz[a] * sz[b];        // w is path-min for these cross pairs
        if(sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
    }
    cout << ans << '\n';
}