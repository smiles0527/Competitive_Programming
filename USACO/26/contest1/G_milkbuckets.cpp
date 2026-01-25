#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int N=200005;
int b[N],n;

void upd(int i,int x){for(;i<=n;i+=i&-i)b[i]+=x;}
int qry(int i){int s=0;for(;i>0;i-=i&-i)s+=b[i];return s;}
struct D{ll v;int i;};
bool cmp(D x,D y){return x.v>y.v;}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;cin>>t;
    while(t--){
        cin>>n;
        vector<D> a(n);
        for(int i=0;i<n;i++){cin>>a[i].v;a[i].i=i+1;}

        if(n<3){cout<<"0\n";continue;}
        sort(a.begin(),a.end(),cmp);

        for(int i=1;i<=n;i++)b[i]=0;
        for(int i=1;i<=n;i++)upd(i,1);

        ll ans=0;
        int rem=0,i=0;

        while(i<n && rem<n-2){
            int j=i;
            while(j<n && a[j].v==a[i].v) j++;

            deque<int> q;
            for(int k=i;k<j;k++) q.push_back(a[k].i);
            sort(q.begin(),q.end());

            while(q.size() && rem<n-2){
                int u=q.front(), v=q.back();
                int pu=qry(u), pv=qry(v), sz=n-rem;

                int cu=min(pu-1, sz-pu);
                int cv=min(pv-1, sz-pv);

                if(cu<=cv){
                    ans+=cu; upd(u,-1); q.pop_front();
                } else {
                    ans+=cv; upd(v,-1); q.pop_back();
                }
                rem++;
            }
            i=j;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
