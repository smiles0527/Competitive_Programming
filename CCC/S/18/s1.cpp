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


    double count = INT_MAX;

    for (int i = 1; i < n-1; i++){
        count = min(count,((double)arr[i]-(double)arr[i-1])/2 + ((double)arr[i+1]-(double)arr[i])/2);
    }

    cout << setprecision(2) << count << "\n";
}