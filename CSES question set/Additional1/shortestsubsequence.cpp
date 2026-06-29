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

    string s; cin >> s;
    string chars = "AGCST";
    set<char> seen;
    string ans;

    for(char c : s){
        seen.insert(c);
        if(seen.size() == 4){
            ans += c;
            seen.clear();
        }
    }

    for(char c : chars){
        if(!seen.count(c)){ ans += c; break; }
    }

    cout << ans << '\n';
}