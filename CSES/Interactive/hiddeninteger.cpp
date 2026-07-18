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
    int lo = 1, hi = 1e9;
    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        cout << "? " << mid << "\n" << flush;
        string r; cin >> r;
        if(r == "YES") lo = mid + 1;
        else hi = mid;
    }
    cout << "! " << lo << "\n" << flush;
    return 0;
}