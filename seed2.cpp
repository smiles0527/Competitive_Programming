#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long left = 1;
    long long right = (long long) 2e9;

    while (true)
    {
        long long mid = left + (right-left)/2;
        cout << mid << "\n";
        cout.flush();
        
        string s;
        cin >> s;
        if (s == "OK") return 0;
        if (s == "SINKS") left = mid+1;
        if (s == "FLOATS") right = mid-1;
    }
}