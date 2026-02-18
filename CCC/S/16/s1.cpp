#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    vector<int> freq1(26,0);
    vector<int> freq2(26,0);

    int star = 0;

    for (char c : s1){
        freq1[c-'a']++;
    }

    for (char c : s2){
        if (c == '*'){
            star++;
        }
        else{
            freq2[c-'a']++;
        }
    }

    for (int i = 0; i < 26; i++){
        if (freq2[i] > freq1[i]){
            cout << "N";
            return 0;
        }
    }
    cout << "A";
}