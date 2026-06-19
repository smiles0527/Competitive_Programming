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

    int n; cin >> n;
    vector<int> arr(n-1);
    int moves = 0;
    int steps = 0;

    for(int i = 0; i < n - 1; i++){
        if(arr[i+1] < arr[i]){
            steps += arr[i] - arr[i+1];
        } else {
            
        }
        moves += steps;
    }

    return 0;
}