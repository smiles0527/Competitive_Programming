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
    string out; out.reserve(m * 12);
    while(m--){
        int a, b; cin >> a >> b;
        if(a > b) swap(a, b);            // orient low -> high
        out += to_string(a); out += ' ';
        out += to_string(b); out += '\n';
    }
    cout << out;
}