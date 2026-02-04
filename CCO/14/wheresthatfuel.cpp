#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,p; cin>>n>>p;
    long long r=0;
    vector<pair<int,int>> v;
    vector<int> z;

    for(int i=1;i<=n;i++){
        int a,b; cin>>a>>b;
        if(i==p){ r=a; continue; }
        int d=a-b;
        if(d>0) v.push_back({b,d});
        else if(d==0) z.push_back(b);
    }

    sort(v.begin(), v.end());

    long long k=0;
    int c=0;

    /*
      treat each planet i as an action:
        need fuel >= b_i, then fuel += (a_i - b_i)
      if (a_i - b_i) <= 0 it never raises fuel, so it can't help reach higher b_j.
      so max fuel: take all reachable (a_i - b_i) > 0 in increasing b_i order (fuel only increases).
      after max fuel M is fixed, extra planets with (a_i - b_i)=0 can be appended if b_i <= M (fuel unchanged).
    */

    for(auto &e: v){
        if((long long)e.first>r) break;
        r += e.second;
        c++;
    }

    for(int b: z) if((long long)b<=r) k++;

    cout<<r<<"\n"<<(1LL+c+k)<<"\n";
    return 0;
}
