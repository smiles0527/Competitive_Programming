#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> h(n+1);
    for(int i=1;i<=n;i++) cin >> h[i];

    vector<int> L(n+1), R(n+1);
    vector<int> st;
    for(int i=1;i<=n;i++){                       // nearest >= to left
        while(!st.empty() && h[st.back()] < h[i]) st.pop_back();
        L[i] = st.empty()?0:st.back();
        st.push_back(i);
    }
    st.clear();
    for(int i=n;i>=1;i--){                        // nearest >= to right
        while(!st.empty() && h[st.back()] < h[i]) st.pop_back();
        R[i] = st.empty()?n+1:st.back();
        st.push_back(i);
    }

    vector<int> idx(n); iota(idx.begin(),idx.end(),1);
    sort(idx.begin(),idx.end(),[&](int a,int b){return h[a]<h[b];});

    int sz=1; while(sz<max(n,1)) sz<<=1;
    vector<int> tr(2*sz,0);
    auto upd=[&](int p,int v){ p+=sz-1; tr[p]=v;
        for(p>>=1;p;p>>=1) tr[p]=max(tr[2*p],tr[2*p+1]); };
    auto qry=[&](int l,int r)->int{ if(l>r) return 0;
        int res=0; l+=sz-1; r+=sz-1;
        while(l<=r){ if(l&1)res=max(res,tr[l++]);
                     if(!(r&1))res=max(res,tr[r--]); l>>=1; r>>=1; }
        return res; };

    int ans=0;
    for(int i: idx){                              // ascending height
        int f = 1 + max(qry(L[i]+1,i-1), qry(i+1,R[i]-1));
        ans = max(ans,f);
        upd(i,f);
    }
    cout << ans << "\n";		
}	