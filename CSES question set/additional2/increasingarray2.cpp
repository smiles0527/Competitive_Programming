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
    int n; cin >> n;
    priority_queue<ll> pq;                       // max-heap: slope breakpoints of convex prefix cost
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll x; cin >> x;
        pq.push(x);
        if(pq.top() > x){                        // running max exceeds x => flatten down to x
            ans += pq.top() - x;
            pq.pop();
            pq.push(x);                          // median-merge: kink stays at x
        }
    }
    cout << ans << "\n";
}