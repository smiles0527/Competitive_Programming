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

    int n, m; cin >> n >> m;
    vector<int> h(m+1, 0);
    ll ans = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char c; cin >> c;
            h[j] = (c == '.') ? h[j] + 1 : 0;
        }
        h[m] = 0; 

        vi st;

        for(int j = 0; j <= m; j++){
            while(!st.empty() && h[st.back()] >= h[j]){
                ll ht = h[st.back()]; st.pop_back();
                ll L = st.empty() ? -1 : st.back();
                ans = max(ans, ht * (j - L - 1));
            }
            st.pb(j);
        }
    }
    cout << ans << '\n';
}