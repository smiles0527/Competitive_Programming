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

    vector<int> cnt(k+2, 0);          // only values in [0,k] matter
    set<int> absent;
    for(int val = 0; val <= k; val++) absent.insert(val);

    auto add = [&](int x){
        if(x <= k && cnt[x]++ == 0) absent.erase(x);
    };
    auto rem = [&](int x){
        if(x <= k && --cnt[x] == 0) absent.insert(x);
    };

    string out;
    for(int i = 0; i < n; i++){
        add(v[i]);
        if(i >= k) rem(v[i-k]);
        if(i >= k-1){
            out += to_string(*absent.begin());
            out += ' ';
        }
    }
    cout << out << "\n";
    return 0;
}