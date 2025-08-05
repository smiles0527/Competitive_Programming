#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> arr(n-1);
    int moves = 0;
    int steps = 0;

    for(int i = 0; i < n - 1; i++){
        if(arr[i+1] < arr[i]){
            steps += arr[i] - arr[i+1];
        } else {
            
        }
        moves += steps;
    }
}