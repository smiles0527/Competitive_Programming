#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while(T--){
        int N; long long K; cin >> N >> K;
        long long g = llabs(K), s = (K > 0 ? 1 : -1);
        vector<vector<long long>> grp((size_t)g);
        for(int i=0;i<N;i++){
            long long a; cin >> a;
            long long b = s * a;
            long long r = b % g; if(r < 0) r += g;
            long long c = (b - r) / g;
            grp[(size_t)r].push_back(c);
        }

        long long ans = 0;

        for(auto &v: grp){
            if(v.empty()) continue;
            sort(v.begin(), v.end());
            long long nx = (long long)-4e18;
            for(long long x: v){
                if(x < nx){ ans += (nx - x); x = nx; }
                nx = x + 1;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}