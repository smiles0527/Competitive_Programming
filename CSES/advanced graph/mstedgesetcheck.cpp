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

int tp[100005], iq[100005], curq;          // throwaway DSU, stamped per group
int tfnd(int x){
    if(iq[x] != curq){ iq[x] = curq; tp[x] = x; return x; }   // fresh this group
    int r = x;
    while(tp[r] != r) r = tp[r];
    while(tp[x] != r){ int nx = tp[x]; tp[x] = r; x = nx; }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    vector<array<int,3>> e(m);              // (a, b, w) by edge id
    vector<int> ord(m);
    for(int i = 0; i < m; i++){
        int a, b, w; cin >> a >> b >> w;
        e[i] = {a, b, w}; ord[i] = i;
    }
    sort(ord.begin(), ord.end(), [&](int x, int y){ return e[x][2] < e[y][2]; });

    vector<char> ans(q, 1);                 // YES until a level fails
    vector<array<int,4>> qe; qe.reserve(m); // (w, qid, a, b)
    for(int qid = 0; qid < q; qid++){
        int k; cin >> k;
        while(k--){ int id; cin >> id; --id; qe.pb({e[id][2], qid, e[id][0], e[id][1]}); }
    }
    sort(qe.begin(), qe.end(), [](const array<int,4>&x, const array<int,4>&y){
        return x[0] != y[0] ? x[0] < y[0] : x[1] < y[1];
    });

    for(int i = 1; i <= n; i++){ p[i] = i; sz[i] = 1; }

    int gi = 0, i = 0, Q = (int)qe.size();
    while(i < Q){
        int w = qe[i][0];
        while(gi < m && e[ord[gi]][2] < w){            // advance frontier: edges < w
            int id = ord[gi++], a = fnd(e[id][0]), b = fnd(e[id][1]);
            if(a != b){ if(sz[a] < sz[b]) swap(a, b); p[b] = a; sz[a] += sz[b]; }
        }
        int j = i;
        while(j < Q && qe[j][0] == w){                 // groups of same (w, qid)
            int g = j, qid = qe[j][1];
            while(g < Q && qe[g][0] == w && qe[g][1] == qid) g++;
            curq++;
            for(int t = j; t < g; t++){                 // forest check on lighter frontier
                int x = tfnd(fnd(qe[t][2])), y = tfnd(fnd(qe[t][3]));
                if(x == y) ans[qid] = 0; else tp[x] = y;
            }
            j = g;
        }
        i = j;
    }

    string out; out.reserve(q * 4);
    for(int t = 0; t < q; t++) out += ans[t] ? "YES\n" : "NO\n";
    cout << out;
}