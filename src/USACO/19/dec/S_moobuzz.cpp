#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("moobuzz.in", "r", stdin);
    freopen("moobuzz.out", "w", stdout);

    long long n; cin >> n;
    vector<int> a {1, 2, 4, 7, 8, 11, 13, 14};

    int y = (n - 1) / 8;
    int x = (n - 1) % 8;

    long long answer = y * 15 + a[x];

    cout << answer << '\n';
    return 0;
}