#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
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