#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool ge_pow(ll b, int e, ll N) {
    __int128 r = 1, B = b;
    while (e) {
        if (e & 1) {
            r *= B;
            if (r >= N) return true;
        }
        B *= B;
        if (B >= N) B = N;
        e >>= 1;
    }
    return r >= N;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q; cin >> Q;
    while(Q--){
        int t; ll N;
        cin >> t >> N;
        if(t == 1){
            int F; cin >> F;
            ll lo = 1, hi = N, k = N;
            while(lo <= hi){
                ll m = (lo + hi) / 2;
                if(ge_pow(m, F, N)){
                    k = m;
                    hi = m - 1;
                } else lo = m + 1;
            }
            cout << (k - 1) << "\n";
        } else {
            ll D; cin >> D;
            ll base = D + 1, p = 1;
            int F = 0;
            while(p < N){
                p = min<__int128>(p * base, N);
                F++;
            }
            cout << F << "\n";
        }
    }
    return 0;
}