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

    vector<int> srt(v);
    sort(srt.begin(), srt.end());
    srt.erase(unique(srt.begin(), srt.end()), srt.end());
    int m = srt.size();
    for(int i = 0; i < n; i++)
        v[i] = lower_bound(srt.begin(), srt.end(), v[i]) - srt.begin();

    vector<int> cnt(m, 0);
    vector<set<int>> bucket(k+1);     // bucket[f] = compressed values with freq f
    int maxf = 0;
    string out;
    for(int i = 0; i < n; i++){
        int u = v[i];
        if(cnt[u]) bucket[cnt[u]].erase(u);
        cnt[u]++;
        bucket[cnt[u]].insert(u);
        if(cnt[u] > maxf) maxf = cnt[u];
        if(i >= k){
            int w = v[i-k];
            bucket[cnt[w]].erase(w);
            cnt[w]--;
            if(cnt[w]) bucket[cnt[w]].insert(w);
            while(maxf > 0 && bucket[maxf].empty()) maxf--;
        }
        if(i >= k-1){
            out += to_string(srt[*bucket[maxf].begin()]);
            out += ' ';
        }
    }
    cout << out << "\n";
    return 0;
}