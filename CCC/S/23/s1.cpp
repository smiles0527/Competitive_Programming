#include <bits/stdc++.h>
using namespace std;

int main(){
    int c;
    cin >> c;
    vector<int> a1(c);
    vector<int> a2(c);

    for (int i = 0; i < c; i++){
        cin >> a1[i];
    }
    for (int i = 0; i < c; i++){
        cin >> a2[i];
    }
    
    int black = 0; 
    for (int i = 0; i < c; i++){
        if (a1[i] == 1){
            black++;
        }
        if (a2[i] == 1){
            black++;
        }
    }

    int h = 0;

    for (int i = 0; i+1 < c; i++){
        if (a1[i] == 1 && a1[i+1] == 1){
            h++;
        }
        if (a2[i] == 1 && a2[i+1] == 1){
            h++;
        }
    }

    int v = 0;

    for (int i = 0; i < c; i++){
        if ((i % 2 == 0) && a1[i] == 1 && a2[i] == 1){
            v++;
        }
    }

    int tot = 3 * black - 2 * (h + v);
    cout << tot << "\n";
}