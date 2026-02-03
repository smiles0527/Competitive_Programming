#include <bits/stdc++.h>
using namespace std;

int main(){
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    int p1 = 2*a + 2*x + 2*(max(b,y));
    int p2 = 2*(max(a,x)) + 2*b + 2*y;
    cout << min(p1, p2);

}