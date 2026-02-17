#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, s, h;
    cin >> t >> s >> h;

    string g(s, ' ');
    string pr = "*" + g + "*" + g + "*";

    FOR(i,0,t) cout << pr << "\n";
    cout << string(3 + 2*s, '*') << "\n";

    string ind(1 + s, ' ');
    FOR(i,0,h) cout << ind << "*\n";
}
