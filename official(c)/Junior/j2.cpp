#include <iostream>
using namespace std;

int main() {
    int d, e;
    cin >> d >> e;
    int current = d;
    
    for (int i = 0; i < e; i++) {
        string op;
        int q;
        cin >> op >> q;
        if (op == "+") {
            current += q;
        } else {
            current -= q;
        }
    }
    
    cout << current << endl;
    return 0;
}