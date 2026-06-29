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
    vii a;
    for(int i = 0; i < n; i++){
        ll x; cin >> x;
        a.pb({x, i});
    }
    sort(a.begin(), a.end());
    
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans = max(ans, (int)a[i].s - i);
    }
    cout << ans << '\n';
}