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

struct DSU{
    vector<int> p, sz, xr;
    DSU(int n){
        p.resize(n+1);
        sz.assign(n+1, 1);
        xr.assign(n+1, 0);
        iota(p.begin(), p.end(), 0);
    }
    pair<int,int> find(int x){
        if(p[x]==x) return {x, 0};
        auto q = find(p[x]);
        p[x] = q.f;
        xr[x] ^= q.s;
        return {p[x], xr[x]};
    }
    bool unite(int a, int b, int w){
        auto A = find(a), B = find(b);
        int ra = A.f, rb = B.f, xa = A.s, xb = B.s;
        if(ra==rb) return ((xa^xb)==w);
        if(sz[ra] < sz[rb]){
            swap(ra, rb);
            swap(xa, xb);
        }
        p[rb] = ra;
        xr[rb] = xa^xb^w;
        sz[ra] += sz[rb];
        return true;
    }
    int val(int x){
        return find(x).s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> v(n);
    for(auto& z : v) cin >> z;

//    vector<int> s1, s2; s1.reserve(n); s2.reserve(n);
//    vector<char> ans(n);
//    int need = 1; bool ok = true;
//
//    for(int i = 0; i < n && ok; i++){
//        while(true){                                          // pop all exposed needed values
//            if(!s1.empty() && s1.back()==need){ s1.pop_back(); need++; }
//            else if(!s2.empty() && s2.back()==need){ s2.pop_back(); need++; }
//            else break;
//        }
//        int x = v[i];
//        int t1 = s1.empty()? INT_MAX : s1.back();
//        int t2 = s2.empty()? INT_MAX : s2.back();             // empty = INF reserve
//        if(t1 > x && t2 > x){                                 // smallest top > x dominates
//            if(t1 <= t2){ s1.pb(x); ans[i]='1'; } else { s2.pb(x); ans[i]='2'; }
//        } else if(t1 > x){ s1.pb(x); ans[i]='1'; }
//        else if(t2 > x){ s2.pb(x); ans[i]='2'; }
//        else ok = false;                                      // both tops < x => stuck
//    }
//
//    if(!ok){ cout << "IMPOSSIBLE\n"; return 0; }
//    string out; out.reserve(2*n);
//    for(int i = 0; i < n; i++){ out += ans[i]; out += (i+1<n? ' ' : '\n'); }
//    cout << out;

    vector<int> mn(n+1, INF);
    for(int i = n-1; i >= 0; i--) mn[i] = min(mn[i+1], v[i]);

    DSU dsu(n);
    set<int> act, bad;
    bool ok = true;

    auto add = [&](int x){
        auto it = act.lower_bound(x);
        if(it != act.begin()) bad.erase(*prev(it));
        auto cur = act.insert(x).f;
        if(cur != act.begin()) bad.insert(*prev(cur));
        if(next(cur) != act.end()) bad.insert(x);
    };

    for(int i = 0; i < n && ok; i++){
        int x = v[i];

        if(mn[i+1] < x){
            int l = mn[i+1]+1, r = x-1;
            auto it = act.lower_bound(l);

            if(it != act.end() && *it <= r){
                int rep = *it;
                auto jt = bad.lower_bound(l);

                while(jt != bad.end()){
                    int a = *jt;
                    if(a >= r) break;

                    auto ia = act.find(a);
                    auto ib = next(ia);
                    if(ib == act.end()){
                        jt = bad.erase(jt);
                        continue;
                    }

                    int b = *ib;
                    if(b > r) break;

                    if(!dsu.unite(a, b, 0)){
                        ok = false;
                        break;
                    }
                    jt = bad.erase(jt);
                }

                if(ok && !dsu.unite(x, rep, 1)) ok = false;
            }
        }

        if(ok) add(x);
    }

    if(!ok){
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for(int i = 0; i < n; i++){
        cout << dsu.val(v[i])+1 << " \n"[i+1==n];
    }
}