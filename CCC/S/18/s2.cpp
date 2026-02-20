#include <bits/stdc++.h>
using namespace std;

int arrange(vector<vector<int>>& arr, int n){
    for (int r = 0; r < n; r++){
        for (int c = 0; c+1 < n; c++){
            if (arr[r][c+1] > arr[r][c]){
                continue;
            }
            else{
                return 0;
            }
        }
    }

    for (int r = 0; r+1 < n; r++){
        for (int c = 0; c < n; c++){
            if (arr[r][c] < arr[r+1][c]){
                continue;
            }
            else{
                return 0;
            }
        }
    }
    return 1;
}

vector<vector<int>> rotate(vector<vector<int>>& arr, int n){
    vector<vector<int>> a1(n, vector<int>(n));
    for (int r = 0; r < n; r++){
        for (int c = 0; c < n; c++){
            a1[c][n-r-1] = arr[r][c];
        }
    }
    return a1;
}

void print(vector<vector<int>>& arr, int n){
    for (int r = 0; r < n; r++){
        for (int c = 0; c < n; c++){
            cout << arr[r][c] << " ";
        }
        cout << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> arr(n, vector<int>(n));
    for (int r = 0; r < n; r++){
        for (int c = 0; c < n; c++){
            cin >> arr[r][c];
        }
    }

    while (true){
        if (arrange(arr, n) == 1){
            print(arr, n);
            break;
        }
        else{
            arr = rotate(arr, n);
        }
    }
}