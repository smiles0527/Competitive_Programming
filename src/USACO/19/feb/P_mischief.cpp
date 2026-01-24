//TLE on test case 4-14

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define FOR(i, a, b) for(int (i) = (a); i < (b); i++)

struct State{
    int len;
    long long area;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);
    int N; int T;
    cin >> N >> T;

    // vector<pair<ll, ll>> flowers(N);
    // FOR(i, 0, N) cin >> flowers[i].first >> flowers[i].second;
    // ll area = T * T;
    // int total = 1 << N;

    vector<pair<ll, ll>> points(N);
    points.emplace_back(0, 0);
    FOR(i, 0, N){
        long long x; long long y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    points.emplace_back(T, T);
    sort(points.begin(), points.end());

    //============

    int M = points.size();
    vector<State> dp(M, State{-1, INT_MAX});
    dp[0] = {0, 0};


    // vector<long long> dp(M, INT_MAX);
    
    auto better = [&](const State& a, const State& b){
        if(a.len != b.len) return a.len > b.len;
        return a.area < b.area;
    };

    for(int j = 1; j < M; j++){
        for(int i = 0; i < j; i++){
            if(dp[i].len < 0) continue;
            if(points[i].second > points[j].second) continue;

            if(points[i].second <= points[j].second){
                long long dx = points[j].first - points[i].first;
                long long dy = points[j].second - points[i].second;
                long long add = dx * dy;

                int addlen = (j != 0 && j != M - 1) ? 1 : 0;
                //max check
                State cand{dp[i].len + addlen, dp[i].area + add};

                if(dp[j].len < 0 || better(cand, dp[j])) dp[j] = cand;
            }
        }
    }

    //dp[end] = dp[0]


    // bool visited = true;
    // impossible
    // for(int i = 0; i + 1 < (int)points.size(); i++){
    //     if(points[i].first < points[i+1].first){
    //         visited = false; 
    //         break;
    //     }
    // }
    /*
    long long dx = points[i+1].first - points[i].second;
    long long dy = points[i+1].second - points[i].second;
    */
    //possible
    
    // if(!visited) continue;
    
    // long long totalarea = 0;
    // for(int i = 0; i + 1 < (int)points.size(); i++){
    //     long long dx = points[i+1].first - points[i].second;
    //     long long dy = points[i+1].second - points[i].second;
        
    // }
    // area = min(area, totalarea);

    cout << dp[M-1].area << '\n';
    return 0;



}