#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;
    string r(s.rbegin(), s.rend());

    vector<int> prv(n + 1, 0), cur(n + 1, 0);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++)
            cur[j] = (s[i - 1] == r[j - 1]) ? prv[j - 1] + 1
                                            : max(prv[j], cur[j - 1]);
        swap(prv, cur);                 // prv now holds row i
    }
    cout << n - prv[n] << "\n";         // n - LPS
    return 0;
}