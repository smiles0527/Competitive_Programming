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
    vi h(n+1);
    for(int i = 0; i < n; i++) cin >> h[i];
    h[n] = 0;                       // sentinel flushes stack

    vi st;                          // indices, increasing height
    ll ans = 0;
    for(int i = 0; i <= n; i++){
        while(!st.empty() && h[st.back()] >= h[i]){
            ll ht = h[st.back()]; st.pop_back();
            ll L = st.empty() ? -1 : st.back();   // nearest smaller left
            ans = max(ans, ht * (i - L - 1));
        }
        st.pb(i);
    }
    cout << ans << '\n';
}