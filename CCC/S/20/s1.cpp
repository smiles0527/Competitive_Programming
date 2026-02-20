#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<pair<int, int>> arr(n);

    for (int i = 0; i < n; i++){
        cin >> arr[i][0] >> arr[i][1];
    }
     sort(arr.begin(), arr.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });
}