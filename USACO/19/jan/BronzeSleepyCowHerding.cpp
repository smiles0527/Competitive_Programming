#include <bits/stdc++.h>
using namespace std;
//bronze
int main(){

    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    vector<int> arr(3);
    for (int i = 0; i < 3; i++){
        cin >> arr[i];
    }
    bool consec = false;
    bool big = false;
    for (int i = 0; i+1 < 3; i++){
        if (arr[i+1] - arr[i] == 1){
            consec = true;
        }
        else if (arr[i+1] - arr[i] > 1){
            big = true;
        }
    }

    if ()
}