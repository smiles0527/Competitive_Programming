#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    int count = 0;
    for (int i = 0; i < n / 4; i++){
        if (n % 4 == 0 || (n - 4 * i) %  5 == 0){
            count++;
        }
    }
    cout << count;
}