#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using P = pair<ll,int>;
using OST = tree<P, null_type, less<P>, rb_tree_tag, tree_order_statistics_node_update>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; ll mn;
    if(!(cin>>n>>mn)) return 0;
    OST t;
    ll d=0;
    long long lefted=0;
    int uid=0;
    for(int i=0;i<n;i++){
        char op; ll k; 
        cin>>op>>k;
        if(op=='I'){
            if(k>=mn) t.insert({k-d, uid++});
        }else if(op=='A'){
            d+=k;
        }else if(op=='S'){
            d-=k;
            ll thr = mn - d;
            while(!t.empty()){
                auto it=t.begin();
                if(it->first < thr){ t.erase(it); lefted++; }
                else break;
            }
        }else if(op=='F'){
            int sz = (int)t.size();
            if(k>sz) cout<<-1<<"\n";
            else{
                auto it = t.find_by_order(sz-(int)k);
                cout<<it->first + d<<"\n";
            }
        }
    }
    cout<<lefted<<"\n";
    return 0;
}
