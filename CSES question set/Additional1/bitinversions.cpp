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

    string str; cin >> str;
    int n = str.size();

    set<int> B = {0, n};                      // active boundaries + sentinels
    multiset<int> lens;
    vector<char> brk(n+1, 0);                 // brk[i]: s_i != s_{i+1}, i in 1..n-1

    auto addGap = [&](int a, int b){ lens.insert(b - a); };
    auto delGap = [&](int a, int b){ lens.erase(lens.find(b - a)); };

    for(int i = 1; i < n; i++)
        if(str[i-1] != str[i]){ brk[i] = 1; B.insert(i); }

    {                                         // initial gap lengths
        int prev = 0;
        for(int b : B) if(b != 0){ lens.insert(b - prev); prev = b; }
    }

    auto toggle = [&](int i){
        if(i < 1 || i > n-1) return;
        auto it = B.find(i);
        if(it != B.end()){                    // remove boundary, merge gaps
            int lo = *prev(it), hi = *next(it);
            delGap(lo, i); delGap(i, hi); addGap(lo, hi);
            B.erase(it); brk[i] = 0;
        } else {                              // insert boundary, split gap
            auto nx = B.lower_bound(i);
            int hi = *nx, lo = *prev(nx);
            delGap(lo, hi); addGap(lo, i); addGap(i, hi);
            B.insert(i); brk[i] = 1;
        }
    };

    int m; cin >> m;
    string out; out.reserve(m*7);
    while(m--){
        int x; cin >> x;
        str[x-1] ^= 1;                        // flip toggles boundaries x-1 and x
        toggle(x-1);
        toggle(x);
        out += to_string(*lens.rbegin());
        out += '\n';
    }
    cout << out;
}