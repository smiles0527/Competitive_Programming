#include <bits/stdc++.h>
using namespace std;

bool yesNo(int n, string l, string r){
    int jj = 0, jn = 0, nj = 0, nn = 0;

    for (int i = 0; i < n; i++){
        if (l[i] == 'J' && r[i] == 'J'){
            jj++;
        }
        else if (l[i] == 'J' && r[i] == 'N'){
            jn++;
        }
        else if (l[i] == 'N' && r[i] == 'J'){
            nj++;
        }
        else{
            nn++;
        }
    }

    if (jn != nj){
        return false;
    }
    if ((jn+nn) % 2 != 0){
        return false;
    }

    return true;
}

void perm(int n, string l, string r){

}

int main(){
    int t, c;
    cin >> t >> c;
 
    for (int i = 0; i < t; i++){
        int n;
        string left, right;
        cin >> n >> left >> right;

        bool ans = yesNo(n, left, right);

        if (ans){
            cout << "YES" << "\n";
            if (c==1){
            perm(n, left, right);
            }
        }
        else{
            cout << "NO" << "\n";
        }
    }
}