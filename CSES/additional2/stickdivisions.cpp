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
    ll x; int n; cin >> x >> n;
    priority_queue<ll, vector<ll>, greater<ll>> pq;       // min-heap of stick lengths
    for(int i = 0; i < n; i++){ ll d; cin >> d; pq.push(d); }

    ll ans = 0;
    while(pq.size() > 1){                                  // Huffman merge: combine two smallest
        ll a = pq.top(); pq.pop();
        ll b = pq.top(); pq.pop();
        ans += a + b; pq.push(a + b);
    }
    cout << ans << "\n";
}