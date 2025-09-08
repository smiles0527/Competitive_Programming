#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    using OSet = tree<pair<long long,int>, null_type, less<pair<long long,int>>, rb_tree_tag, tree_order_statistics_node_update>;
    int N;
    if(!(cin >> N)) return 0;
    OSet T;
    const int MAXID = 1000000;
    vector<long long> id2rating(MAXID + 2, LLONG_MIN);
    for(int i=0;i<N;i++){
        char op;
        cin >> op;
        if(op=='N'){
            int x; long long r;
            cin >> x >> r;
            id2rating[x]=r;
            T.insert({-r,x});
        }else if(op=='M'){
            int x; long long r;
            cin >> x >> r;
            long long old = id2rating[x];
            T.erase({-old,x});
            id2rating[x]=r;
            T.insert({-r,x});
        }else{
            long long k;
            cin >> k;
            auto it = T.find_by_order((size_t)k-1);
            cout << it->second << '\n';
        }
    }
    return 0;
}
