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
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];

    multiset<int> lo, hi;            // lo: smaller half (top = median), hi: larger half
    // int t = (k + 1) / 2;             // target size of lo
    auto rebalance = [&](){
        int t = ((int)(lo.size()+hi.size()) + 1) / 2;   // lower-median split for current count
        while((int)lo.size() > t){ auto it = prev(lo.end()); hi.insert(*it); lo.erase(it); }
        while((int)lo.size() < t){ auto it = hi.begin(); lo.insert(*it); hi.erase(it); }
    };
    auto add = [&](int x){
        if(lo.empty() || x <= *lo.rbegin()) lo.insert(x);
        else hi.insert(x);
        rebalance();
    };
    auto rem = [&](int x){
        auto it = lo.find(x);
        if(it != lo.end()) lo.erase(it);
        else hi.erase(hi.find(x));
        rebalance();
    };

    string out;
    for(int i = 0; i < n; i++){
        add(v[i]);
        if(i >= k) rem(v[i-k]);
        if(i >= k-1){
            out += to_string(*lo.rbegin());
            out += ' ';
        }
    }
    cout << out << "\n";
    return 0;
}