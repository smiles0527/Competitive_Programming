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
    int n, m, k; cin >> n >> m >> k;
    vector<ii> e(m);
    unordered_map<ll,int> id; id.reserve(2*m);
    auto key = [&](int a, int b) -> ll { if(a > b) swap(a, b); return (ll)a*(n+1) + b; };
    for(int i = 0; i < m; i++){ cin >> e[i].f >> e[i].s; id[key(e[i].f, e[i].s)] = i; }

    vi brk(k); vector<char> dead(m, 0);       // edge idx per breakdown
    for(int i = 0; i < k; i++){ int a, b; cin >> a >> b; int j = id[key(a, b)]; brk[i] = j; dead[j] = 1; }

    for(int i = 1; i <= n; i++){ p[i] = i; sz[i] = 1; }
    int cur = n;
    for(int i = 0; i < m; i++) if(!dead[i]){  // surviving graph = state after all k breakdowns
        int a = fnd(e[i].f), b = fnd(e[i].s);
        if(a != b){ if(sz[a] < sz[b]) swap(a, b); p[b] = a; sz[a] += sz[b]; cur--; }
    }

    vi ans(k + 1); ans[k] = cur;
    for(int i = k - 1; i >= 0; i--){          // re-add breakdown i+1 -> ans[i]
        int j = brk[i];
        int a = fnd(e[j].f), b = fnd(e[j].s);
        if(a != b){ if(sz[a] < sz[b]) swap(a, b); p[b] = a; sz[a] += sz[b]; cur--; }
        ans[i] = cur;
    }

    string out; out.reserve(k * 8);
    for(int i = 1; i <= k; i++){ out += to_string(ans[i]); out += " \n"[i == k]; }
    cout << out;
}