#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    string str; 
    cin >> str;

    int maxlen = 1;
    int curlen = 1;
    for(int i = 0; i < str.length() - 1; i++){
        if(str[i + 1] == str[i]){
            curlen++;
        }else {
            curlen = 1;
        }

        if(curlen > maxlen) maxlen = curlen;
    }
    cout << maxlen;
}