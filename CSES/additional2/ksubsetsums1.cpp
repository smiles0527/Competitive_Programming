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
    int n; ll k; cin >> n >> k;
    vector<ll> a(n); ll base = 0;
    for(auto& x : a){ cin >> x; if(x < 0){ base += x; x = -x; } }   // shift: sums = base + subset sums of |x|
    sort(a.begin(), a.end());

    string out; out.reserve(k * 12);
    out += to_string(base); out += ' ';                            // empty subset = base
    // states (sum, i): i = last index included; children add or swap-up the next index
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    if(n) pq.push({a[0], 0});
    for(ll cnt = 1; cnt < k; cnt++){
        auto [s, i] = pq.top(); pq.pop();
        out += to_string(base + s); out += ' ';
        if(i + 1 < n){
            pq.push({s + a[i+1], i+1});                             // add next
            pq.push({s - a[i] + a[i+1], i+1});                      // swap last for next
        }
    }
    cout << out;
}