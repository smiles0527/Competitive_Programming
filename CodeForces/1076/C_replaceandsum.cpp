#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n, q; cin >> n >> q;
    vector<int> a(n); for(auto &x:a) cin >> x;
    vector<int> b(n); for(auto &x:b) cin >> x;
    
    vector<long long> v(n);
    long long mx = 0;
    for(int i = n - 1; i >=0; i--){
        mx = max(mx, (long long)max(a[i], b[i]));
        v[i] = mx;
    }

    vector<long long> pref(n+1, 0);
    for(int i = 0; i < n; i++) pref[i+1]=pref[i]+v[i];
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        cout << pref[r] - pref[l-1] << (i + 1 == q ? '\n' : ' ');
    }
    

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}