#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<double>a(N);
    for(int i=0; i<N; i++) cin >> a[i];

    double lo = *min_element(a.begin(), a.end());
    double hi = *max_element(a.begin(), a.end());

    auto ok = [&](double X){
        vector<double> S(N+1);
        for(int i=1; i<=N; i++){
            S[i] = S[i-1] + (a[i-1] - X);
        }
        double min_pref = 0;
        for(int i=K; i<=N; i++){
            min_pref = min(min_pref, S[i-K]);
            if(S[i] - min_pref >= 0) return true;
        }
        return false;
    };

    for(int it=0; it<60; it++){
        double mid = (lo + hi) / 2;
        if(ok(mid)) lo = mid; else hi = mid;
    }

    cout << fixed << setprecision(6) << lo << "\n";
    return 0;
}
