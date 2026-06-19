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
	
	int t; cin >> t;
    while(t--){
        ll y, x; cin >> y >> x;
        ll k = max(y, x), v;
        if(k & 1){                       // odd layer
            if(x == k) v = k*k - y + 1;
            else       v = (k-1)*(k-1) + x;
        } else {                         // even layer
            if(y == k) v = k*k - x + 1;
            else       v = (k-1)*(k-1) + y;
        }
        cout << v << "\n";
    }

	return 0;
}