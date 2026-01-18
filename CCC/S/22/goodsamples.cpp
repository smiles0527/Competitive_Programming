#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a;
    for(ll i = 0; i < n; i++){
        ll x = n-i-1;
        ll y = min(k-x, m);
        if(y <= 0) break;
        ll z;
        if(y>i){
            z = min(m, i+1);
            y = z;
        }
        else z = a[i-y];
        a.push_back(z);
        k -= y;
    }
    if(k == 0 && (ll)a.size() == n){
        for(auto x : a) cout << x << " ";
        cout << endl;
    }
    else cout << -1 << endl;
}