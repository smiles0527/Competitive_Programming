#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;

    ll sa = accumulate(a.begin(), a.end(), 0LL), sb = accumulate(b.begin(), b.end(), 0LL);
    if(sa != sb){ cout << -1 << "\n"; return 0; }

    vector<string> g(n, string(n, '.'));
    vector<int> col(b);                                  // residual column demand
    for(int i = 0; i < n; i++){
        // place a[i] X's into columns of largest residual demand (Gale-Ryser greedy)
        vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int p, int q){ return col[p] > col[q]; });
        if(a[i] > n){ cout << -1 << "\n"; return 0; }
        for(int t = 0; t < a[i]; t++){
            int c = idx[t];
            if(col[c] <= 0){ cout << -1 << "\n"; return 0; }   // not enough columns with demand
            g[i][c] = 'X'; col[c]--;
        }
    }
    for(int c = 0; c < n; c++) if(col[c] != 0){ cout << -1 << "\n"; return 0; }   // leftover demand

    string out; out.reserve((size_t)n*(n+1));
    for(auto& r : g){ out += r; out += '\n'; }
    cout << out;
}