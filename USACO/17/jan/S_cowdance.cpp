#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("cowdance.in", "r", stdin);
    freopen("cowdance.out", "w", stdout);

    int N, Tmax; cin >> N >> Tmax;
    vector<int> d(N);
    FOR(i, 0, N) cin >> d[i];

    int lo = 1, hi = N;
    while(lo<hi){
        int mid = lo + (hi-lo)/2;  

        priority_queue<long long, vector<long long>, greater<long long>> pq;
        FOR(i, 0, mid) pq.push(d[i]);
        FOR(i, mid, N){ ll t = pq.top(); pq.pop(); pq.push(t + d[i]); }

        ll T = 0;
        while(!pq.empty()){ T = max(T, pq.top()); pq.pop(); }
        
       if(T <= Tmax) hi = mid; 
       else lo = mid + 1; 

    }
    cout << lo << "\n";
    return 0;
}