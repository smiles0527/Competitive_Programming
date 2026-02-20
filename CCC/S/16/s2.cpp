#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    int n;
    cin >> n;
    vector<int> a1(n);
    vector<int> a2(n);

    for (int i = 0; i < n; i++){
        cin >> a1[i];
    }
    for (int i = 0; i < n; i++){
        cin >> a2[i];
    }

    sort(a1.begin(), a1.end());
    sort(a2.begin(), a2.end());
    
    int count = 0;
    if (q == 1){
        for (int i = 0; i < n; i++){
            count += max(a1[i], a2[i]);
        }
    }
    else{
        reverse(a2.begin(), a2.end());
        for (int i = 0; i < n; i++){
            count += max(a1[i], a2[i]);
        }
    }

    cout << count;
}