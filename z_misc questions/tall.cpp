#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    if(!(cin >> T)) return 0;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i=0;i<n;i++) cin >> a[i];
        unordered_set<int> S;
        S.reserve(n*2);
        for(int x: a) S.insert(x);
        vector<int> vals;
        vals.reserve(S.size());
        for(int x: S) vals.push_back(x);
        int m = -1;
        int a = INT_MAX;
        int limit = (int)S.size();
        for(int k: vals){
            int x = 0;
            while(x <= limit && S.find(k ^ x) != S.end()) ++x;
            if(x > m || (x == m && k < a)){
                m = x;
                a = k;
            }
            if(m == limit) break;
        }
        cout << m << " " << a << "\n";
    }
    return 0;
}
