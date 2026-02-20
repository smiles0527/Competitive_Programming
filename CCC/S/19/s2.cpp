#include <bits/stdc++.h>
using namespace std;

bool prime(int n){
    
    int count = 0;
    for (int i = 1; i <= n; i++){
        if (n % i == 0){
            count++;
        }
    }

    if (count > 2){
        return false;
    }
    else if (count == 1){
        return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        arr[i] *= 2;
    }

    vector<bool> t(n, false);

    for (int i = 0; i < n; i++){

        vector<pair<int, int>> a;
    

        for (int j = 3; j < arr[i]; j++){
            if (prime(j)){
                int x = arr[i] - j;
                if (x >= 0 && prime(x)){
                    if (j <= x && !t[i]){
                        a.push_back({j, x});
                        t[i] = true;
                    }
                }
            }
        }

        for (int j = 0; j < a.size(); j++){
        cout << a[j].first << " " << a[j].second << "\n";
        }
    }

    
}