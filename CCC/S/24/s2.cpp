#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int t, n;
    cin >> t >> n;

    for (int i = 0; i < t; i++){
        vector<bool> heavy(26);
        vector<int> count(26,0);

        string str;
        cin >> str;
        for (int i = 0; i < n; i++){
            count[str[i]-'a']++;
        }

        for (int i = 0; i < 26; i++){
            if (count[i] > 1){
                heavy[i] = true;
            }
        }

        bool alex = true;

        for (int i = 0; i + 1 < n; i++){
            if ((heavy[str[i]-'a'] && !heavy[str[i+1]-'a']) || (!heavy[str[i]-'a'] && heavy[str[i+1]-'a'])){
                continue;
            }
            else{
                alex = false;
                break;
            }
        }

        if (alex){
            cout << "T" << "\n";
        }
        else{
            cout << "F" << "\n";
        }

    }
}