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
const ll INF = 4e18;
 
struct P{
    ll x, y;
    int id;
};
 
struct BIT{
    int n; vi bit;
    BIT(int n = 0): n(n), bit(n+1, -INF) {}
    void upd(int i, ll v){
        for(; i <= n; i += i & -i) bit[i] = max(bit[i], v);
    }
    ll qry(int i){
        ll r = -INF;
        for(; i; i -= i & -i) r = max(r, bit[i]);
        return r;
    }
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m; cin >> n >> m;
    vector<P> a(n), b(m);
 
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
        a[i].id = -1;
    }
 
    for(int i = 0; i < m; i++){
        cin >> b[i].x >> b[i].y;
        b[i].id = i;
    }
 
    vi ans(m, INF);
    for(int sx : {-1, 1}){
        for(int sy : {-1, 1}){
            vector<P> r, q;
            vi ys;
 
            for(auto p : a){
                p.x *= sx;
                p.y *= sy;
                r.pb(p);
                ys.pb(p.y);
            }
            for(auto p : b){
                p.x *= sx;
                p.y *= sy;
                q.pb(p);
                ys.pb(p.y);
            }
 
            sort(ys.begin(), ys.end());
            ys.erase(unique(ys.begin(), ys.end()), ys.end());
 
            sort(r.begin(), r.end(), [](P a, P b){
                return a.x < b.x;
            });
 
            sort(q.begin(), q.end(), [](P a, P b){
                return a.x < b.x;
            });
 
            BIT ft(ys.size());
            int j = 0;
 
            for(auto p : q){
                while(j<n && r[j].x <= p.x){
                    int y = lower_bound(ys.begin(), ys.end(), r[j].y) - ys.begin() + 1;
                    ft.upd(y, r[j].x + r[j].y);          // store c_x + c_y
                    j++;
                }
 
                int y = upper_bound(ys.begin(), ys.end(), p.y) - ys.begin();
                ll best = ft.qry(y);
 
                if(best != -INF){
                    ans[p.id] = min(ans[p.id], p.x + p.y - best);
                }
            }
        }
    }
    for(int i = 0; i < m; i++) cout << ans[i] << " \n"[i==m-1];
}