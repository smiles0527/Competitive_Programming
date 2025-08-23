#include <bits/stdc++.h>
using namespace std;
int main(){
    long long A, B, X, Y;
    cin >> A >> B >> X >> Y;
    long long c1 = 2 * (A + X + max(B, Y));
    long long c2 = 2 * (max(A, X) + B + Y);
    cout << min(c1, c2);
    return 0;
}
