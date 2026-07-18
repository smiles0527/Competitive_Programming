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

int m;
vector<int> bit;
void upd(int i, int d){ for(; i <= m; i += i&-i) bit[i] += d; }
int qry(int i){ int s = 0; for(; i > 0; i -= i&-i) s += bit[i]; return s; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];

    vector<int> srt(v);
    sort(srt.begin(), srt.end());
    srt.erase(unique(srt.begin(), srt.end()), srt.end());
    m = srt.size();
    for(int i = 0; i < n; i++)
        v[i] = lower_bound(srt.begin(), srt.end(), v[i]) - srt.begin() + 1; // 1-indexed ranks

    bit.assign(m+1, 0);
    ll inv = 0;
    int sz = 0;
    string out;
    for(int i = 0; i < n; i++){
        inv += sz - qry(v[i]);       // new element vs larger predecessors in window
        upd(v[i], 1); sz++;
        if(i >= k-1){
            out += to_string(inv);
            out += ' ';
            int w = v[i-k+1];        // leftmost, about to leave
            upd(w, -1); sz--;
            inv -= qry(w-1);         // its inversions = remaining elements smaller than it
        }
    }
    cout << out << "\n";
    return 0;
}