#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll t; cin >> t;
    vector<ll> a(t); for(auto &x: a) cin >> x;
    sort(a.begin(), a.end());

    ll x = -1, y = 0;
    for(int i=0;i<t;++i){
        ll tt = a[i];
        ll r = tt*(t-i);
        if(r > x || (r==x && tt<y)) x = r, y = tt;
    }

    cout << x << ' ' << y << '\n';
    
    return 0;
}