#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    char sillied, silly;
    char quiet = '-';
    
    vector<int> freq1(26);
    vector<int> freq2(26);
    for (int i = 0; i < s1.size(); i++){
        freq1[s1[i] - 'a']++;
    }
    for (int i = 0; i < s2.size(); i++){
        freq2[s2[i] - 'a']++;
    }

    int c = 0;
    for (int i = 0; i < s2.size(); i++){
        if (s1[i + c] != s2[i]){
            int diff = s1[i+c] - s2[i];
            int n = diff;

            while (n == diff){
                c++;
                if (i + c == s1.length()){
                    break;
                }
                n = s1[i+c] - s2[i];
            }

            if (i + c < s1.length() && s1[i+c] == s2[i])
            {
                quiet = s1[i+c-1];
            }
            else{
                sillied = s1[i+c-1];
                silly = s2[i];
                break;
            }
        }
    }

    if (quiet == '-'){
        for (int i = 0; i < 26; i++){
            char cur = char(i + 'a');
            if (freq2[i] == 0 && freq1[i] > 0 && cur != sillied){
                quiet = cur;
            }
        }
    }
    cout << sillied << " " << silly << endl << quiet << endl;
}