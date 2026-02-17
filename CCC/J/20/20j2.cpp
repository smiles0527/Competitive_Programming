#include <iostream>
using namespace std;
#define ll long long

int main() {
    long long P, N, R;
    cin >> P >> N >> R;

    long long day = 0;
    long long total = N;
    long long cur = N;

    while (total <= P) {
        day++;
        cur *= R;
        total += cur;
    }

    cout << day;
    return 0;
}
