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

const char* NM[6] = {"FILL A","FILL B","EMPTY A","EMPTY B","MOVE A B","MOVE B A"};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b, x; cin >> a >> b >> x;
    int B1 = b + 1;
    int N = (a + 1) * B1;

    vector<ll> dist(N, INF);
    vector<int> par(N, -1);
    vector<char> mv(N, -1);

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    dist[0] = 0; pq.push({0, 0});            // (0,0)

    while(!pq.empty()){
        auto [d, id] = pq.top(); pq.pop();
        if(d > dist[id]) continue;
        int p = id / B1, q = id % B1;

        for(int k = 0; k < 6; k++){
            int np = p, nq = q; ll c = 0;
            if(k==0){ c=a-p; np=a; }
            else if(k==1){ c=b-q; nq=b; }
            else if(k==2){ c=p; np=0; }
            else if(k==3){ c=q; nq=0; }
            else if(k==4){ ll t=min((ll)p,(ll)(b-q)); c=t; np=p-t; nq=q+t; }
            else        { ll t=min((ll)q,(ll)(a-p)); c=t; np=p+t; nq=q-t; }
            if(c <= 0) continue;             // must move ≥1 unit

            int nid = np*B1 + nq;
            ll nd = d + c;
            if(nd < dist[nid]){
                dist[nid] = nd; par[nid] = id; mv[nid] = (char)k;
                pq.push({nd, nid});
            }
        }
    }

    int best = -1; ll bd = INF;
    if(x <= a)
        for(int q = 0; q <= b; q++){
            int id = (int)x*B1 + q;
            if(dist[id] < bd){ bd = dist[id]; best = id; }
        }

    if(best < 0){ cout << -1 << '\n'; return 0; }

    vector<int> seq;                         // reconstruct backwards
    for(int cur = best; cur != 0; cur = par[cur]) seq.pb(mv[cur]);
    reverse(seq.begin(), seq.end());

    cout << seq.size() << ' ' << bd << '\n';
    for(int k : seq) cout << NM[k] << '\n';
}