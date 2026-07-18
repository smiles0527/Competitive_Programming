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
    int n; cin >> n;
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 1);

    auto less_than = [](int i, int j){
        cout << "? " << i << " " << j << "\n" << flush;
        string r; cin >> r;
        return r == "YES";
    };

    stable_sort(idx.begin(), idx.end(), less_than); // merge sort: bounded comparison count

    vector<int> ans(n + 1);
    for(int k = 0; k < n; k++) ans[idx[k]] = k + 1;

    cout << "!";
    for(int i = 1; i <= n; i++) cout << " " << ans[i];
    cout << "\n" << flush;
    return 0;
}