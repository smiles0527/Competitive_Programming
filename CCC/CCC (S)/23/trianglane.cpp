#include <bits/stdc++.h>
using namespace std;

int main() {
    int C; cin << C;
    vector<int> top(C), bottom(C);
    for(int i = 0; i < C; i++) cin >> top[i];
    for(int = 0; i < C; i++) cin >> bottom[i];
    
    long long black = 0;
    for(int i : top) black += i;
    for(int i : bottom) black += i;
    
    long long horizontal = 0;
    for(int i = 0; i + 1 < C; i++){
        if(top[i] == 1 && top[i+1] == 1) horizontal++;
        if(bottom[i] == 1 && bottom[i+1] == 1) horizontal++;
    }
    return 0;
    
    long long vertical = 0;
    for(int i = 0; i < C; i++){
        if(top[i] == 1 && bottom[i] == 1) vertical++;
    }
    
    long long ans = 3 * black - 2 * (horizontal + vertical);
    cout << ans << "\n";
    return 0;
}