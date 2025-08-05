#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x,y;
    cin>>x>>y;
    if(y>x) swap(x,y);

    vector<array<char,3>> ops;
    long long t=y;
    while(t>0){
        if(t&1) ops.push_back({'A','C','C'});
        t>>=1;
        if(t>0) ops.push_back({'A','A','A'});
    }

    cout<<ops.size()<<"\n";
    for(auto &o:ops)
        cout<<o[0]<<" "<<o[1]<<" "<<o[2]<<"\n";
    cout<<"C\n";
    return 0;
}
    