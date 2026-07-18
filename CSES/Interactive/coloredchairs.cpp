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

int n;
vector<int> cache;

int col(int i){
    if(cache[i] != -1) return cache[i];
    cout << "? " << i << "\n" << flush;
    string r; cin >> r;
    return cache[i] = (r == "B");
}

int main(){
    cin >> n;
    cache.assign(n+1, -1);

    int c1 = col(1), cn = col(n);
    if(c1 == cn){ cout << "! " << n << "\n" << flush; return 0; }

    // f(i) = c_i ^ c1 ^ ((i-1)&1); f(1)=0, f(n)=1, locate the flip
    int lo = 1, hi = n;
    while(hi - lo > 1){
        int mid = (lo + hi) / 2;
        int fm = col(mid) ^ c1 ^ ((mid-1)&1);
        if(fm == 0) lo = mid;
        else hi = mid;
    }

    cout << "! " << lo << "\n" << flush;
    return 0;
}