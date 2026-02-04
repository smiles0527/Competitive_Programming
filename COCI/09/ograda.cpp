#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;
    vector<int> h(n+1);
    for(int i=1;i<=n;i++) cin>>h[i];

    int w=n-m+1;
    vector<int> mn(max(1,w+1));
    deque<int> d;

    for(int i=1;i<=n;i++){
        while(!d.empty()&&h[d.back()]>=h[i]) d.pop_back();
        d.push_back(i);
        if(d.front()<=i-m) d.pop_front();
        if(i>=m){
            int l=i-m+1;
            if(l>=1&&l<=w) mn[l]=h[d.front()];
        }
    }

    vector<int> f(n+1);
    deque<int> q;
    int L=1,R=0;

    for(int i=1;i<=n;i++){
        int a=max(1,i-m+1), b=min(i,w);
        while(R<b){
            ++R;
            while(!q.empty()&&mn[q.back()]<=mn[R]) q.pop_back();
            q.push_back(R);
        }
        while(L<a){
            if(!q.empty()&&q.front()==L) q.pop_front();
            ++L;
        }
        f[i]=(a<=b?mn[q.front()]:0);
    }

    long long man=0;
    for(int i=1;i<=n;i++) man+=h[i]-f[i];

    unordered_map<int,vector<int>> p,s;
    for(int i=1;i<=n;i++) p[f[i]].push_back(i);
    for(int i=1;i<=w;i++) s[mn[i]].push_back(i);

    long long ans=0;

    for(auto &kv:p){
        int v=kv.first;
        if(!s.count(v)) continue;
        auto &pt=kv.second;
        auto &st=s[v];
        long long cr=0,br=0;
        int j=0;
        for(int x:pt){
            while(j<(int)st.size()&&st[j]<=x){
                br=max(br,(long long)st[j]+m-1);
                j++;
            }
            if(x>cr){
                cr=br;
                ans++;
            }
        }
    }

    cout<<man<<"\n"<<ans<<"\n";
    return 0;
}
