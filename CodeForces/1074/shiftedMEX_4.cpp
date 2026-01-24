#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int> arr(n);
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }

        // O(n) approach
        unordered_set<int> s(arr.begin(), arr.end());
        int minimum = *min_element(arr.begin(), arr.end());
        int maxmex = 0;
        for(int start : s){
            int mex = 0;
            while(s.count(start + mex)){
                mex++;
            }
            maxmex = max(maxmex, mex);
        }



        // O(n log n) approach
        // sort(arr.begin(), arr.end());
        // for(int i = 0; i < n; i++){
        //     arr[i] = arr[i] - arr[0];
        // }
        
        // int mex = 0;
        // for(int i = 0; i < n; i++){
        //     if(arr[i] == mex){
        //         mex++;
        //     }
        // }
        
        
        cout << maxmex << "\n";


    }

    return 0;
}