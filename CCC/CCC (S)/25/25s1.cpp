#include <bits/stdc++.h>
using namespace std;
int main(){
    long long A, B, X, Y;
    cin >> A >> B >> X >> Y;
    long long candidate1 = 2 * (A + X + max(B, Y));
    long long candidate2 = 2 * (max(A, X) + B + Y);
    cout << min(candidate1, candidate2);
    return 0;
}
