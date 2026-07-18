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
    int q; cin >> q;
    while(q--){
        ull k; cin >> k;
        ull d = 1, cnt = 9, st = 1;          // d-digit block: count cnt, start value st
        while(k > d * cnt){ k -= d * cnt; d++; cnt *= 10; st *= 10; }
        ull num = st + (k - 1) / d;          // which number
        int pos = (k - 1) % d;               // digit index within it
        cout << to_string(num)[pos] << "\n";
    }
}