#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    vector<int> arr;
    for (int i = 0; i < k; i++){
        int n; 
        cin >> n;
        if (n != 0){
            arr.push_back(n);
        }
        else{
            arr.pop_back();
        }
    }

    int count = 0;
    for (int i : arr){
        count += i;
    }
    
    cout << count;
}