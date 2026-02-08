#include <bits/stdc++.h>
using namespace std;

int main(){
    int num, denom;
    cin >> num >> denom;

    if (num == 0){
        cout << 0 << "\n";
        return 0;
    }

    int whole = num / denom;
    int r = num % denom;

    if (r == 0){
        cout << whole << "\n";
        return 0;
    }

    long long gcd = __gcd(r, denom);

    r /= gcd;
    denom /= gcd;

    if (whole == 0){
        cout << r << "/" << denom << "\n";
    }
    else{
        cout << whole << " " << r << "/" << denom << "\n";
    }
}