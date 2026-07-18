#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> p(n + 1, 0);
    for (int i = 1; i <= n; i++){
        ll x; cin >> x;
        p[i] = p[i-1] + x;
    }

    while (q--){
        int a, b; cin >> a >> b;
        cout << p[b] - p[a-1] << '\n';
    }
    return 0;
}