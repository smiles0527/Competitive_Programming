#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k; cin>>n>>k;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];

    if(k<=1){
        long long nn=n;
        cout<<nn*(nn+1)/2<<"\n";
        return 0;
    }

    unordered_map<int,int> mp;
    mp.reserve((size_t)n*2+7);
    mp.max_load_factor(0.7f);

    long long ans=0;
    int d=0,l=0;

    /*
      sliding window for "at most k-1 distinct"
      count = total - atMost(k-1)
      (classic inclusion: >=k distinct = total - <=k-1 distinct)
      each step r: expand, then shrink until d<=k-1, add window size
    */
    for(int r=0;r<n;r++){
        int x=a[r];
        auto it=mp.find(x);
        if(it==mp.end()){ mp.emplace(x,1); d++; }
        else it->second++;

        while(d>k-1){
            int y=a[l++];
            auto jt=mp.find(y);
            jt->second--;
            if(jt->second==0){ mp.erase(jt); d--; }
        }
        ans += (r-l+1);
    }

    long long tot=1LL*n*(n+1)/2;
    cout<<(tot-ans)<<"\n";
    return 0;
}
