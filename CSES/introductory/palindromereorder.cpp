#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s, h, m;
    cin >> s;

    int c[26] = {};

    for (char x : s) c[x - 'A']++;

    for (int i = 0; i < 26; i++) {
        if (c[i] % 2) m += char('A' + i);
        h += string(c[i] / 2, char('A' + i));
    }

    if (m.size() > 1) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    string r = h;
    reverse(r.begin(), r.end());
    cout << h << m << r << '\n';
    

    return 0;
}
