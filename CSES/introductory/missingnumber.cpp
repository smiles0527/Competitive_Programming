#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;

    long  long sum = 0;
    for(int i = 0; i < n - 1; i++){
        long long x = 0; cin >> x;
        sum += x;
    }
    cout << n*(n+1)/2 - sum;
    

    return 0;
}
