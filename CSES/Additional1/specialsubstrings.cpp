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

struct Hsh {
    static ull splm(ull x){
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x>>30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x>>27)) * 0x94d049bb133111ebULL;
        return x ^ (x>>31);
    }
    size_t operator()(ull x) const {
        static const ull FIX = chrono::steady_clock::now().time_since_epoch().count();
        return splm(x + FIX);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const ull P = (1ULL<<61) - 1;            // additive hash field
    string str; cin >> str;
    int n = str.size();

    vector<int> pr;                          // distinct chars present
    vector<char> seen(26, 0);
    for(char c : str) seen[c-'a'] = 1;
    for(int c = 0; c < 26; c++) if(seen[c]) pr.pb(c);

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<ull> w(26, 0);
    ull sum = 0;
    for(int i = 0; i+1 < (int)pr.size(); i++){
        w[pr[i]] = rng() % P;
        sum = (sum + w[pr[i]]) % P;
    }
    if(!pr.empty()) w[pr.back()] = (P - sum) % P;   // total weight ≡ 0 (mod P)

    unordered_map<ull, int, Hsh> cnt;
    cnt.reserve(n*2);
    cnt[0] = 1;                              // empty prefix
    ull h = 0; ll ans = 0;
    for(char c : str){
        h += w[c-'a']; if(h >= P) h -= P;
        ans += cnt[h]++;                     // equal prefix vector ⇒ special
    }
    cout << ans << '\n';
}