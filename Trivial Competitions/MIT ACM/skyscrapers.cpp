#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    long long c, C;
    if(!(cin >> M >> N >> c >> C)) return 0;

    vector<int> W(M), S(N);
    for(int i = 0; i < M; i++) cin >> W[i];
    for(int j = 0; j < N; j++) cin >> S[j];

    int maxW = *max_element(W.begin(), W.end());
    int maxS = *max_element(S.begin(), S.end());
    if(maxW != maxS){
        cout << "Impossible\n";
        return 0;
    }

    const int MAXH = 20000;
    vector<long long> cntW(MAXH+1), cntS(MAXH+1);
    long long sumW = 0, sumS = 0;
    for(int h : W){
        cntW[h]++;
        sumW += h;
    }
    for(int h : S){
        cntS[h]++;
        sumS += h;
    }

    long long shared = 0;
    for(int h = 0; h <= MAXH; h++){
        long long m = min(cntW[h], cntS[h]);
        shared += m * h;
    }

    long long minSum = sumW + sumS - shared;

    sort(S.begin(), S.end());
    vector<long long> prefix(N+1);
    prefix[0] = 0;
    for(int i = 0; i < N; i++){
        prefix[i+1] = prefix[i] + S[i];
    }

    long long maxSum = 0;
    for(int w : W){
        int k = upper_bound(S.begin(), S.end(), w) - S.begin();
        maxSum += prefix[k] + 1LL * (N - k) * w;
    }

    long long minPop = minSum * c;
    long long maxPop = maxSum * C;
    cout << "Minimum: " << minPop << ", maximum: " << maxPop << "\n";

    return 0;
}
