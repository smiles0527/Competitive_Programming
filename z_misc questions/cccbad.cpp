#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        string s; cin>>s;
        int k; cin>>k;
        int n=(int)s.size();

        if(k>=n){
            sort(s.begin(), s.end());
            cout<<s<<"\n";
            continue;
        }

        vector<char> st, rm;
        st.reserve(n); rm.reserve(k);

        /*
          think: final = kept (in original order) + moved_digits (we can schedule moves to make them sorted)
          using <=k moves, making number smallest => always spend moves to delete digits that block smaller ones
          so: keep lexicographically smallest subsequence of length n-k (classic remove-k stack)
          the removed k digits just get appended sorted at the end
        */

        int kk=k;
        for(char c: s){
            while(kk && !st.empty() && st.back()>c){
                rm.push_back(st.back());
                st.pop_back();
                kk--;
            }
            st.push_back(c);
        }
        while(kk){
            rm.push_back(st.back());
            st.pop_back();
            kk--;
        }

        sort(rm.begin(), rm.end());

        string out;
        out.reserve(n);
        for(char c: st) out.push_back(c);
        for(char c: rm) out.push_back(c);

        cout<<out<<"\n";
    }
    return 0;
}
