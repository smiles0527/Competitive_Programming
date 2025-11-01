#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    if(!(cin>>n>>q)) return 0;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    const int B = 31;
    vector<array<int,2>> ch;
    vector<int> mn;
    ch.push_back({-1,-1});
    mn.push_back(INT_MAX);
    auto addNode = [&](){
        ch.push_back({-1,-1});
        mn.push_back(INT_MAX);
        return (int)ch.size()-1;
    };
    for(int i=0;i<n;i++){
        int node = 0;
        mn[node] = min(mn[node], i);
        for(int b = B-1; b >= 0; --b){
            int bit = (a[i] >> b) & 1;
            if(ch[node][bit] == -1) ch[node][bit] = addNode();
            node = ch[node][bit];
            mn[node] = min(mn[node], i);
        }
    }
    int X = 0;
    while(q--){
        int x; cin>>x;
        X ^= x;
        int node = 0;
        for(int b = B-1; b >= 0; --b){
            int want = (X >> b) & 1;
            if(ch[node][want] != -1) node = ch[node][want];
            else node = ch[node][want ^ 1];
        }
        cout << mn[node] << '\n';
    }
    return 0;
}
