#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        int n, m; ll h; cin >> n >> m >> h;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        } 
        vector<ll> b(a);

        vector<ll> add(n, 0);
        vector<ll> seen(n);
        int reset = -1;

        vector<pair<int, ll>> ops(m);
        for(int i = 0; i < m; i++){
            cin >> ops[i].first >> ops[i].second;
            ops[i].first--; 
        }

        for(int i = 0; i < m; i++){
            int idx = ops[i].first;
            ll val = ops[i].second;

            if(seen[idx] != reset){
                seen[idx] = reset;
                add[idx] = 0;
            }

            add[idx] += val;
            if(b[idx] + add[idx] > h){
                reset++;
            }
        }

        for(int i = 0; i < n; i++){
            ll extra = (seen[i] == reset ? add[i] : 0);
            cout << b[i] + extra << " ";
        }



        
        // Crashing every time: O(nm) approach (very very slow)
        // for(int i = 0; i < m; i++){
        //     a[ops[i].first] += ops[i].second;
        //     if(a[ops[i].first] > h){
        //         a = b;
        //     }
        // }

        // for(int i = 0; i < a.size(); i++){
        //     cout << a[i] << " ";
        // }
        cout << "\n";
    }
    
    return 0;
}