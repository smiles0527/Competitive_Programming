#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class GroupValidator {
    unordered_map<string, int> groups;
    vector<pair<string, string>> together, separate;

public:
    void process() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        
        int X, Y, G;
        string a, b, c;
        
        cin >> X;
        together.reserve(X);
        while (X--) {
            cin >> a >> b;
            together.emplace_back(a, b);
        }
        
        cin >> Y;
        separate.reserve(Y);
        while (Y--) {
            cin >> a >> b;
            separate.emplace_back(a, b);
        }
        
        cin >> G;
        for (int i = 0; i < G; ++i) {
            cin >> a >> b >> c;
            groups[a] = i;
            groups[b] = i;
            groups[c] = i;
        }
        
        int cnt = 0;
        for (auto& [s1, s2] : together)
            cnt += (groups[s1] != groups[s2]);
        
        for (auto& [s1, s2] : separate)
            cnt += (groups[s1] == groups[s2]);
        
        cout << cnt;
    }
};

int main() {
    GroupValidator solver;
    solver.process();
    return 0;
}
