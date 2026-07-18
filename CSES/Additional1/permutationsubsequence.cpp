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
    vector<int> a(n+1), pa(n+1, 0);
    for(int i = 1; i <= n; i++){ cin >> a[i]; pa[a[i]] = i; }

    vector<int> p, val;                      // p[k]=pos_a[b_k], val[k]=value
    for(int j = 0; j < m; j++){
        int x; cin >> x;
        if(x <= n && pa[x]){ p.pb(pa[x]); val.pb(x); }   // present in a
    }
    int k = p.size();

    // LIS on p (strictly increasing) with reconstruction
    vector<int> tails;                       // tails[len] = seq index
    vector<int> par(k, -1);
    for(int i = 0; i < k; i++){
        int lo = 0, hi = tails.size();
        while(lo < hi){                      // first tail with p >= p[i]
            int md = (lo+hi)/2;
            if(p[tails[md]] < p[i]) lo = md+1; else hi = md;
        }
        if(lo > 0) par[i] = tails[lo-1];
        if(lo == (int)tails.size()) tails.pb(i);
        else tails[lo] = i;
    }

    vector<int> res;
    for(int cur = tails.empty() ? -1 : tails.back(); cur != -1; cur = par[cur])
        res.pb(val[cur]);
    reverse(res.begin(), res.end());

    cout << res.size() << '\n';
    for(int i = 0; i < (int)res.size(); i++) cout << res[i] << " \n"[i+1==(int)res.size()];
    if(res.empty()) cout << '\n';
}