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
    int n; cin >> n;
    int B = 0; while((1<<B) <= n) B++; // bits to encode indices 1..n

    vector<int> a(n+1, 0);
    string b(n, '0');
    for(int t = 0; t < B; t++){
        for(int j = 1; j <= n; j++) b[j-1] = ((j>>t)&1) ? '1' : '0';
        cout << "? " << b << "\n" << flush;
        string r; cin >> r;
        for(int i = 1; i <= n; i++)
            if(r[i-1] == '1') a[i] |= (1<<t);
    }

    cout << "!";
    for(int i = 1; i <= n; i++) cout << " " << a[i];
    cout << "\n" << flush;
    return 0;
}