#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> freq(76,0);

    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        freq[x]++;
    }

    int num = 0;
    for (int i = 75; i >= 0; i--){
        if (freq[i] !=  0){
            num++;
        }
        if (num == 3){
            cout << i << " " << freq[i] << "\n";
            break;
        }
    }
}
