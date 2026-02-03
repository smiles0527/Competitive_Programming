#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n, s, x; cin >> n >> s >> x;
    vector<int> a(n); for(auto &x : a) cin >> x;
    int sum = 0;
    for(auto &x : a) sum += x;

    if(sum <= s && (s-sum) % x == 0) {cout << "YES" << '\n'; return;}
    else cout << "NO" << '\n';

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}