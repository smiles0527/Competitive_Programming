#include <iostream>
using namespace std;

int main() {
    int n, c, p;
    cin >> n >> c >> p;
    int total = c * p;
    cout << (n <= total ? "yes" : "no") << endl;
    return 0;
}