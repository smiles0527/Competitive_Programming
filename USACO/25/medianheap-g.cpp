#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)4e18;

struct Event {
    long long x;
    int type; // 0: makeE, 1: ask, 2: makeL
    int id;   // query id for type=1, otherwise unused
    bool operator<(Event const& o) const {
        if (x != o.x) return x < o.x;
        return type < o.type;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    vector<long long> a(N+1), c(N+1);
    for (int i = 1; i <= N; ++i) cin >> a[i] >> c[i];

    int Q; cin >> Q;
    vector<long long> m(Q);
    for (int i = 0; i < Q; ++i) cin >> m[i];

    vector<int> parent(N+1,0);
    for (int i = 2; i <= N; ++i) parent[i] = i>>1;

    vector<char> state(N+1, 0); // 0:G, 1:E, 2:L
    vector<ll> dpL(N+1,0), dpE(N+1,0), dpG(N+1,0);

    auto selfCost = [&](int i, int cat)->ll{
        if ((int)state[i]==cat) return 0;
        return c[i];
    };

    function<void(int)> recompute = [&](int i){
        ll sL = selfCost(i,2), sE = selfCost(i,1), sG = selfCost(i,0);
        int Lc = i<<1, Rc = (i<<1)|1;
        if (Lc > N) {
            dpL[i]=sL; dpE[i]=sE; dpG[i]=sG;
            return;
        }
        ll L1=dpL[Lc], E1=dpE[Lc], G1=dpG[Lc];
        ll L2=dpL[Rc], E2=dpE[Rc], G2=dpG[Rc];
        ll any1=min({L1,E1,G1}), any2=min({L2,E2,G2}), anyS=min({sL,sE,sG});

        dpL[i]=min({ sL + L1 + any2, sL + L2 + any1, L1 + L2 + anyS });
        dpG[i]=min({ sG + G1 + any2, sG + G2 + any1, G1 + G2 + anyS });
        dpE[i]=min({
            sE + E1 + any2, sE + E2 + any1, E1 + E2 + anyS,
            sE + L1 + G2, sE + G1 + L2,
            E1 + sL + G2, E1 + sG + L2,
            E2 + sL + G1, E2 + sG + L1
        });
    };

    function<void(int)> pullUp = [&](int i){
        while (i) { recompute(i); i >>= 1; }
    };

    for (int i = N; i >= 1; --i) {
        state[i]=0;
        recompute(i);
    }

    unordered_map<long long, vector<int>> byVal;
    byVal.reserve(N*2);
    for (int i = 1; i <= N; ++i) byVal[a[i]].push_back(i);

    vector<Event> ev;
    ev.reserve(2*byVal.size() + Q);
    for (auto &kv : byVal) {
        ev.push_back({kv.first, 0, -1});
        ev.push_back({kv.first, 2, -1});
    }
    for (int i = 0; i < Q; ++i) ev.push_back({m[i], 1, i});
    sort(ev.begin(), ev.end());

    vector<ll> ans(Q,0);

    for (auto &e : ev) {
        if (e.type == 0) {
            auto &vec = byVal[e.x];
            for (int v : vec) { state[v]=1; pullUp(v); }
        } else if (e.type == 1) {
            ans[e.id] = dpE[1];
        } else {
            auto &vec = byVal[e.x];
            for (int v : vec) { state[v]=2; pullUp(v); }
        }
    }

    for (int i = 0; i < Q; ++i) cout << ans[i] << '\n';
    return 0;
}
