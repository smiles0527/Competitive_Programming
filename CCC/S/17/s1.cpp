#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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

    vector<int> as1(n);
    vector<int> as2(n);

    as1[0] = a1[0];
    as2[0] = a2[0];

    for (int i = 1; i < n; i++){
        as1[i] = a1[i] + as1[i-1];
        as2[i] = a2[i] + as2[i-1];
    }

    int count = 0;
    for (int i = 0; i < n; i++){
        if (as1[i] == as2[i]){
            count = max(count, i+1);
        }
    }

    cout << count << endl;
}