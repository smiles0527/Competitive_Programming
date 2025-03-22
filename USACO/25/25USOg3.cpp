#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;
 
ll mod128(__int128 x) {
    x %= MOD;
    if(x < 0) x += MOD;
    return (long long)x;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, A, B;
    ll D;
    cin >> N >> D;
    cin >> A >> B;
    vector<ll> milk(N);
    for (int i = 0; i < N; i++){
        cin >> milk[i];
    }
    sort(milk.begin(), milk.end());
    vector<ll> pref(N+1, 0);
    vector<__int128> preSq(N+1, 0);
    for (int i = 0; i < N; i++){
        pref[i+1] = pref[i] + milk[i];
        preSq[i+1] = preSq[i] + ( __int128 ) milk[i] * milk[i];
    }
    __int128 totalBase = preSq[N];
    ll Tnet = (ll)(A - B) * D;
 
    auto computeFG = [&](int L, int R, ll X, ll D) -> pair<ll, pair<__int128, ll>> {
        int p = int(lower_bound(milk.begin()+L, milk.begin()+R, X - D + 1) - milk.begin());
        int q = int(lower_bound(milk.begin()+L, milk.begin()+R, X) - milk.begin());
        ll cnt1 = p - L;
        ll sum1 = (pref[p] - pref[L]) + D * cnt1;
        ll cnt2 = (max(L, p) < q ? (q - max(L, p)) : 0);
        ll sum2 = X * cnt2;
        ll sum3 = pref[R] - pref[q];
        ll F_val = sum1 + sum2 + sum3;
 
        __int128 G_val = 0;
        if(p > L){
            __int128 part1 = preSq[p] - preSq[L];
            __int128 part2 = 2 * ( __int128 ) D * (pref[p] - pref[L]);
            __int128 part3 = ( __int128 ) D * D * (p - L);
            G_val += part1 + part2 + part3;
        }
        if(q > p){
            ll cnt = q - p;
            G_val += ( __int128 ) X * X * cnt;
        }
        if(R > q){
            G_val += preSq[R] - preSq[q];
        }
        return {F_val, {G_val, 0}};
    };
 
    auto optimalBlock = [&](int L, int R) -> __int128 {
        ll blockSum = pref[R] - pref[L];
        ll target = blockSum + Tnet;
        ll loVal = milk[L], hiVal = milk[R-1] + D;
        ll bestX = loVal;
        while(loVal <= hiVal){
            ll mid = (loVal + hiVal) / 2;
            auto pr = computeFG(L, R, mid, D);
            ll F_mid = pr.first;
            if(F_mid <= target){
                bestX = mid;
                loVal = mid + 1;
            } else {
                hiVal = mid - 1;
            }
        }
        auto pr = computeFG(L, R, bestX, D);
        ll F_base = pr.first;
        __int128 G_base = pr.second.first;
        ll rem = target - F_base;
        __int128 candidate = G_base + rem * (2 * ( __int128 ) bestX + 1);
        return candidate;
    };
 
    int blocks = N - A + 1;
    __int128 bestProfit = 0;
    for (int i = 0; i < blocks; i++){
        int L = i, R = i + A;
        __int128 blockOrig = preSq[R] - preSq[L];
        __int128 optBlock = optimalBlock(L, R);
        __int128 curProfit = (totalBase - blockOrig) + optBlock;
        if(curProfit > bestProfit) bestProfit = curProfit;
    }
    cout << mod128(bestProfit) << "\n";
    return 0;
}
