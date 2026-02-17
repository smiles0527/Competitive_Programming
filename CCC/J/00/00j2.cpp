#include <bits/stdc++.h>
using namespace std;
#define ll long long

char rot(char c){
    if(c=='0') return '0';
    if(c=='1') return '1';
    if(c=='8') return '8';
    if(c=='6') return '9';
    if(c=='9') return '6';
    return '?';
}

bool ok(int x){
    string s = to_string(x);
    string t = s;
    for(int i = 0; i < (int)t.size(); i++){
        t[i] = rot(t[i]);
        if(t[i]=='?') return false;
    }
    reverse(t.begin(), t.end());
    return t == s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    if(m > n) swap(m, n);

    int cnt = 0;
    for(int i = m; i <= n; i++){
        if(ok(i)) cnt++;
    }
    cout << cnt << "\n";
}
