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
    ll slo = 0, shi = 0;             // running sums of each half
    auto rebalance = [&](){
        int t = ((int)(lo.size()+hi.size()) + 1) / 2;
        while((int)lo.size() > t){ auto it = prev(lo.end()); shi += *it; slo -= *it; hi.insert(*it); lo.erase(it); }
        while((int)lo.size() < t){ auto it = hi.begin(); slo += *it; shi -= *it; lo.insert(*it); hi.erase(it); }
    };
    auto add = [&](int x){
        if(lo.empty() || x <= *lo.rbegin()){ lo.insert(x); slo += x; }
        else { hi.insert(x); shi += x; }
        rebalance();
    };
    auto rem = [&](int x){
        auto it = lo.find(x);
        if(it != lo.end()){ lo.erase(it); slo -= x; }
        else { hi.erase(hi.find(x)); shi -= x; }
        rebalance();
    };

    string out;
    for(int i = 0; i < n; i++){
        add(v[i]);
        if(i >= k) rem(v[i-k]);
        if(i >= k-1){
            ll m = *lo.rbegin();
            ll cost = (m*(ll)lo.size() - slo) + (shi - m*(ll)hi.size());
            out += to_string(cost);
            out += ' ';
        }
    }
    cout << out << "\n";
    return 0;
}