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

int p[100005], sz[100005];
int fnd(int x){ while(x != p[x]) x = p[x] = p[p[x]]; return x; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<array<int,4>> e(m);               // (w, a, b, id)
    for(int i = 0; i < m; i++){
        int a, b, w; cin >> a >> b >> w;
        e[i] = {w, a, b, i};
    }
    sort(e.begin(), e.end());                 // light -> heavy
    for(int i = 1; i <= n; i++){ p[i] = i; sz[i] = 1; }

    vector<char> ok(m, 0);
    // group by equal weight: judge against strictly-lighter frontier, then union group
    for(int i = 0; i < m; ){
        int j = i;
        while(j < m && e[j][0] == e[i][0]) j++;
        for(int k = i; k < j; k++)            // decide using only edges < w
            if(fnd(e[k][1]) != fnd(e[k][2])) ok[e[k][3]] = 1;
        for(int k = i; k < j; k++){           // now merge the whole weight class
            int a = fnd(e[k][1]), b = fnd(e[k][2]);
            if(a == b) continue;
            if(sz[a] < sz[b]) swap(a, b);
            p[b] = a; sz[a] += sz[b];
        }
        i = j;
    }

    string out; out.reserve(m * 4);
    for(int i = 0; i < m; i++) out += ok[i] ? "YES\n" : "NO\n";
    cout << out;
}