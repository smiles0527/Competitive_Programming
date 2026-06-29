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

const int MX = 5001;
const int B = 670;                  // # primes ≤ 5000 is 669

ll pw(ll b, ll e){
    ll r = 1; b %= MOD;
    for(; e; e>>=1){ if(e&1) r=r*b%MOD; b=b*b%MOD; }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> spf(MX, 0);                 // smallest prime factor
    vector<int> pid(MX, -1);                // prime -> bit index
    int pc = 0;
    for(int i = 2; i < MX; i++){
        if(!spf[i]){ pid[i] = pc++; for(int j = i; j < MX; j += i) if(!spf[j]) spf[j] = i; }
    }

    int n; cin >> n;
    vector<bitset<B>> rows;                  // basis under elimination
    int r = 0;

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        bitset<B> v;
        while(x > 1){                        // squarefree signature
            int p = spf[x], cnt = 0;
            while(x % p == 0){ x /= p; cnt ^= 1; }
            if(cnt) v.flip(pid[p]);
        }
        for(auto &b : rows){                 // reduce against current basis
            int hb = -1;
            // pivot of b = its highest set bit; reduce greedily
            if((v & b).any()){
                int p = (b._Find_first());
                if(v.test(p)) v ^= b;
            }
        }
        if(v.any()){ rows.pb(v); r++; }
    }

    cout << pw(2, n - r) << '\n';
}