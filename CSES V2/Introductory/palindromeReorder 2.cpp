#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    string n;
    cin >> n;
 
    vector<int> freq(26);
 
    for (char x : n){
        freq[x - 'A']++;
    }
 
    int odd = 0;
    char middle = 0;
 
    for (int i = 0; i < 26; i++){
        if (freq[i] % 2 == 1){
            odd++;
            middle = char('A' + i);
        }
    }
 
    if (odd > 1){
        cout << "NO SOLUTION" << endl;
        return 0;
    }
 
    string left = "";
 
    for (int i = 0; i < 26; i++){
        left += string(freq[i] / 2, char('A' + i));
    }
 
    string right = left;
    reverse(right.begin(), right.end());
 
    cout << left;
 
    if (middle != 0){
        cout << middle;
    }
 
    cout << right;
 
    return 0;
}