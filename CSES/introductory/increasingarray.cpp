#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long previous;
    cin >> previous;

    long long moves = 0;
    for(int i = 1; i < n; i++){
        long long current;
        cin >> current;
        if(current < previous) moves += previous - current;
        else previous = current;
    }

    cout << moves << '\n';

    return 0;
}
