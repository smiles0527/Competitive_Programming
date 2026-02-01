#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll floordiv(ll a, ll b){
    if(b < 0) a = -a, b = -b;
    if(a >= 0) return a / b;
    return - ( ( -a + b - 1 ) / b );
}
ll ceildiv(ll a, ll b){
    return -floordiv(-a, b);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    ll L, R, Y;
    cin >> L >> R >> Y;

    vector<pair<ll,int>> ev;
    ev.reserve(2LL*N);

    for(int i=0;i<N;i++){
        ll x,v,h;
        cin >> x >> v >> h;
        ll d = h * Y;

        ll Li = floordiv(x*v - d, v) + 1;
        ll Ri = ceildiv (x*v + d, v) - 1;

        if(Li <= Ri){
            ev.push_back({Li, +1});
            ev.push_back({Ri+1, -1});
        }
    }

    sort(ev.begin(), ev.end());
    vector<ll> exact(N+1, 0);

    auto addSeg = [&](ll a, ll b, int c){
        a = max(a, L); b = min(b, R);
        if(a <= b) exact[c] += b - a + 1;
    };

    int i = 0, cur = 0;
    ll prev = L;

    while(i < (int)ev.size() && ev[i].first <= L){
        ll p = ev[i].first;
        int d = 0;
        while(i < (int)ev.size() && ev[i].first == p) d += ev[i++].second;
        cur += d;
    }

    while(i < (int)ev.size() && ev[i].first <= R+1){
        ll p = ev[i].first;
        addSeg(prev, p-1, cur);

        int d = 0;
        while(i < (int)ev.size() && ev[i].first == p) d += ev[i++].second;
        cur += d;
        prev = p;
    }
    addSeg(prev, R, cur);

    ll pref = 0;
    for(int k=0;k<=N;k++){
        pref += exact[k];
        cout << pref << "\n";
    }
}

