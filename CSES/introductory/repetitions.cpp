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
    
    string str; cin >> str;
    int ml = 1; int cl = 1;
    for(int i = 0; i < str.length() - 1; i++){
        if(str[i + 1] == str[i]) cl++;
        else cl = 1;
        if(cl > ml) ml = cl;
    }
    cout << ml;

    return 0;
}