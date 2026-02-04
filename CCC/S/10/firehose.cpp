#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    int k; cin >> k;
    sort(a.begin(), a.end());

    const int C = 1000000;

    auto ok = [&](int L)->bool{
        int m = 2*n;
        vector<int> b(m);
        for(int i=0;i<n;i++) b[i]=a[i], b[i+n]=a[i]+C;

        vector<int> nxt(m+1, m);
        int j=0;
        for(int i=0;i<m;i++){
            if(j<i) j=i;
            int lim = b[i] + 2*L;
            while(j<m && b[j]<=lim) j++;
            nxt[i]=j;
        }

        for(int s=0;s<n;s++){
            int p=s;
            for(int t=0;t<k;t++){
                p=nxt[p];
                if(p>=s+n) return true;
                if(p>=2*n) break;
            }
        }
        return false;
    };

    int lo=0, hi=500000;
    while(lo<hi){
        int mid=(lo+hi)/2;
        if(ok(mid)) hi=mid;
        else lo=mid+1;
    }
    cout << lo << "\n";
    return 0;
}
