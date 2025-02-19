#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    long long c;
    cin >> c;
    vector<pair<char, long long>> segs;
    for (size_t i = 0, n = s.size(); i < n; ){
        char ch = s[i++];
        long long num = 0;
        while(i < n && isdigit(s[i])){
            num = num * 10 + (s[i] - '0');
            i++;
        }
        segs.push_back({ch, num});
    }
    long long total = 0;
    for(auto &p : segs) total += p.second;
    long long index = c % total;
    for(auto &p : segs){
        if(index < p.second){
            cout << p.first;
            break;
        }
        index -= p.second;
    }
    return 0;
}
