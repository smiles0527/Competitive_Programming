#include <bits/stdc++.h>
using namespace std;

int SleepyCowHerding() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    int maxMove = max(arr[n-2] - arr[0] - (n-2), arr[n-1] - arr[1] - (n-2));
    
    int j = 0;
    int longest = 0;
    for (int i = 0; i < n; i++){
        while (j < n && arr[j] - arr[i] < n) j++;
        longest = max(longest, j-i);
    }
    
    int minMove = n - longest;
    cout << minMove << "\n" << maxMove << "\n";
}