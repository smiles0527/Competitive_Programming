#include <bits/stdc++.h>
using namespace std;

bool yes(char c) {
    c = (char)tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

string rhyme(string line) {

    int end = line.size() - 1;
    int start = end;
    while (start >= 0 && line[start] != ' '){
        start--;
    }
    start++;

    string word = line.substr(start);
    for (char& c : word){
        c = (char)tolower((unsigned char)c);
    }

    int last = -1;
    for (int i = word.size() - 1; i >= 0; i--) {
        if (yes(word[i])) {
            last = i;
            break;
        }
    }

    if (last == -1){
        return word;
    }
    return word.substr(last);
}

int main() {

    int n;
    cin >> n;
    string temp;
    getline(cin, temp);

    for (int i = 0; i < n; i++){
        string line[4];

        for (int i = 0; i < 4; i++){
        getline(cin, line[i]);
        }

        string s[4];
        for (int i = 0; i < 4; i++){
            s[i] = rhyme(line[i]);
        }

        if (s[0] == s[1] && s[1] == s[2] && s[2] == s[3])
        {
            cout << "perfect\n";
        }
        else if (s[0] == s[1] && s[2] == s[3]){
            cout << "even\n";
        }
        else if (s[0] == s[2] && s[1] == s[3])
        {
            cout << "cross\n";
        }
        else if (s[0] == s[3] && s[1] == s[2]){
            cout << "shell\n";
        }
        else
        {
            cout << "free\n";
        }
    }
    return 0;
}
