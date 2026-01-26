#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int& x : a) cin >> x;
        for (int& x : b) cin >> x;
        
        vector<long long> preb(n + 1);
        for (int i = 0; i < n; i++) {
            preb[i + 1] = preb[i] + b[i];
        }
        
        vector<int> sorted_a = a;
        sort(sorted_a.rbegin(), sorted_a.rend());
        
        long long ans = 0;
        
        for (int i = 0; i < n; i++) {
            int swords = i + 1;
            long long x = sorted_a[i];
            
            int lo = 0, hi = n;
            while (lo < hi) {
                int mid = (lo + hi + 1) / 2;
                if (preb[mid] <= swords) {
                    lo = mid;
                } else {
                    hi = mid - 1;
                }
            }
            
            ans = max(ans, x * lo);
        }
        
        cout << ans << "\n";
    }
}