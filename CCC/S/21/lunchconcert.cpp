#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<ll> P(N), W(N), D(N);
    ll mn = LLONG_MAX, mx = LLONG_MIN;
    for(int i = 0; i < N; i++){
        cin >> P[i] >> W[i] >> D[i];
        mn = min(mn, P[i] - D[i]);
        mx = max(mx, P[i] + D[i]);
    }

    auto cost = [&](ll c){
        ll tot = 0;
        for(int i = 0; i < N; i++){
            ll d = llabs(P[i] - c) - D[i];
            if(d > 0) tot += d * W[i];
        }
        return tot;
    };

    // ternary search on integer interval [mn..mx]
    ll l = mn, r = mx;
    while(r - l > 3){
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        if(cost(m1) < cost(m2)) r = m2 - 1;
        else                 l = m1 + 1;
    }

    ll ans = LLONG_MAX;
    for(ll c = l; c <= r; c++){
        ans = min(ans, cost(c));
    }
    cout << ans << "\n";
    return 0;
}