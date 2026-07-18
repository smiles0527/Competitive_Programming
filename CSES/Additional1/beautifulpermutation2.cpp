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

    if(n==1){ cout << 1 << '\n'; return 0; }
    if(n==2 || n==3){ cout << "NO SOLUTION\n"; return 0; }
    if(n==4){ cout << "2 4 1 3\n"; return 0; }

    vi ans; ans.pb(1), ans.pb(3), ans.pb(5);

    auto block = [&](int a){
        for(int x = a; x <= n && x <= a+8; x += 2) ans.pb(x);
    };

    int r = n % 5;
    if(r == 0 || r == 1){
        for(int a = 2; a <= n; a+= 5) block(a);
    } else{
        int a; vi tail;

        if(r==2){
            a = n - 5;
            tail = {a, a+4, a+2, a+5};
        } else if(r==3){
            a = n - 6;
            tail = {a, a+4, a+6, a+2, a+5};
        } else{
            a = n - 7;
            tail = {a, a+2, a+5, a+7, a+4, a+6};
        }
        for(int b = 2; b < a; b += 5) block(b);
        for(int x : tail) ans.pb(x);
    }
    for(ll x : ans) cout << x << ' ';
    cout << '\n';
}