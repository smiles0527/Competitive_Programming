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

    int n; ll k;
    cin >> n >> k;

    vi a(n);
    for(ll &x : a) cin >> x;

    priority_queue<ii, vii, greater<ii>> pq;

    int r = 0;
    while(r < n && r <= k){
        pq.push({a[r], r});
        r++;
    }

    for(int i = 0; i < n; i++){
        auto [x, id] = pq.top(); pq.pop();
        cout << x << ' ';

        if(r < n){
            pq.push({a[r],r});
            r++;
        }
    }
    cout << '\n';
}