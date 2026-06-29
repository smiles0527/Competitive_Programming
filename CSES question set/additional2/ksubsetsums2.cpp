#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;

// persistent prefix stack; run-node = consecutive index range [s, s+cnt-1] on top, then nxt
struct Node{ int s, cnt, nxt; };
vector<Node> nd;
int pushRun(int h, int s, int cnt){ if(cnt<=0) return h; nd.pb({s,cnt,h}); return (int)nd.size()-1; }
int topv(int h){ return nd[h].s + nd[h].cnt - 1; }                       // value of prefix top = c[r-1]
int popn(int h){ if(nd[h].cnt>1){ nd.pb({nd[h].s, nd[h].cnt-1, nd[h].nxt}); return (int)nd.size()-1; } return nd[h].nxt; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; ll k; cin >> n >> m >> k;
    vector<ll> a(n);
    for(auto& x : a) cin >> x;
    sort(a.begin(), a.end());

    ll S0 = 0; for(int j = 0; j < m; j++) S0 += a[j];      // core = m smallest

    // state (extra, r, cr, ph): combo = frozen prefix(ph) ++ tight run [r,m-1] with values cr..cr+(m-1-r)
    // transitions: A = top++ (old run folds into prefix); B = slot r-1 ++ when gap there == 2 (extends run down)
    nd.clear(); nd.reserve((size_t)2*k + 10);
    priority_queue<tuple<ll,int,int,int>, vector<tuple<ll,int,int,int>>, greater<>> pq;
    pq.push({0LL, 0, 0, -1});                              // base: r=0, cr=0, empty prefix

    string out; out.reserve(k * 12);
    for(ll c = 0; c < k && !pq.empty(); c++){
        auto [e, r, cr, ph] = pq.top(); pq.pop();
        if(c) out += ' ';
        out += to_string(S0 + e);
        int top = cr + (m - 1 - r);                        // c[m-1]
        if(top + 1 <= n - 1){                              // A: increment top
            ll ne = e + a[top+1] - a[top];
            int np = pushRun(ph, cr, m - 1 - r);           // fold tight run [r,m-2] into prefix
            pq.push({ne, m-1, top+1, np});
        }
        if(r >= 1 && ph != -1 && cr - topv(ph) == 2){      // B: gap exactly 2 below the run
            int v = topv(ph);                              // c[r-1] = cr-2
            ll ne = e + a[cr-1] - a[v];
            int np = popn(ph);
            pq.push({ne, r-1, cr-1, np});                  // run extends down to slot r-1
        }
    }
    cout << out << "\n";
}