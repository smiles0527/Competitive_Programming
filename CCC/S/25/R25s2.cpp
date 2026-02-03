#include <bits/stdc++.h>
#include <string>
using namespace std;

int main(){
    string str;
    int c;

    cin >> str >> c;

    int count = 0;
    for (int i = 1; i < str.length(); i+=2){
        count += str.at(i) - '0'; 
    }
    int r = count % (c+1);

    int total = 0;
    int i = 1;
    while (total < r)
    {
        total += str.at(i) - '0'; 
        i+=2;
    }
    cout << str.at(i);
}