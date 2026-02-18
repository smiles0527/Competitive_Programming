#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    int x = (n+1)/2;
    vector<int> a1(arr.begin(), arr.begin() + x);
    vector<int> a2(arr.begin() + x, arr.end());
    
    reverse(a1.begin(), a1.end());

    for (int i = 0; i < a2.size(); i++){
        cout << a1[i] << " " << a2[i] << " ";
    }
    if (n % 2 != 0){
        cout << a1.back();
    }
}