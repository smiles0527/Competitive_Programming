#include <bits/stdc++.h>
using namespace std;

int crop(vector<int> arr, int len, int l){
    int asym = 0;
    int end = l + len;
    for (int i = 0; i < (len+1) / 2; i++){
        asym += abs(arr[i+l] - arr[end]);
        end--;
    }

    return asym;
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    
    vector<int> ans(n);
    for (int i = 1; i < n; i++){
        int mina = INT_MAX;
        for (int j = 0; j < n-i; j++){
            mina = min(mina, crop(arr, i, j));
        }
        ans[i] = mina;
    }

    for (int i : ans){
        cout << i << " ";
    }
    cout << "\n";
}   