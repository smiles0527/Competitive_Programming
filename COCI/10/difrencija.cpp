#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if(!(cin >> N)) return 0;
    vector<long long> a(N);
    for(int i=0;i<N;i++) cin >> a[i];

    vector<int> pg(N), nge(N), ps(N), nse(N);
    vector<int> st;

    st.clear();
    for(int i=0;i<N;i++){
        while(!st.empty() && a[st.back()]<=a[i]) st.pop_back();
        pg[i]=st.empty()? -1:st.back();
        st.push_back(i);
    }
    st.clear();
    for(int i=N-1;i>=0;i--){
        while(!st.empty() && a[st.back()]<a[i]) st.pop_back();
        nge[i]=st.empty()? N:st.back();
        st.push_back(i);
    }

    st.clear();
    for(int i=0;i<N;i++){
        while(!st.empty() && a[st.back()]>=a[i]) st.pop_back();
        ps[i]=st.empty()? -1:st.back();
        st.push_back(i);
    }
    st.clear();
    for(int i=N-1;i>=0;i--){
        while(!st.empty() && a[st.back()]>a[i]) st.pop_back();
        nse[i]=st.empty()? N:st.back();
        st.push_back(i);
    }

    __int128 sumMax=0, sumMin=0;
    for(int i=0;i<N;i++){
        long long L = i - pg[i];
        long long R = nge[i] - i;
        sumMax += (__int128)a[i]*L*R;
    }
    for(int i=0;i<N;i++){
        long long L = i - ps[i];
        long long R = nse[i] - i;
        sumMin += (__int128)a[i]*L*R;
    }
    long long ans = (long long)(sumMax - sumMin);
    cout << ans << "\n";
    return 0;
}
