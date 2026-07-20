//ok so this is my code

```
#include <bits/stdc++.h>
using namespace std;

// helpers
int generate(int n, int x, int a, int b, int c);

int main() {
    int n, k, x, a, b, c;
    if(!(cin >> n >> k >> x >> a >> b >> c)) {
        cout << "segfault";
        return 0;
    }

    vector<int> elements(n);
    for(int i = n-1; i >= 0; i++) {
        elements[i] = generate(i + 1, x, a, b, c);
    }

    vector<int> sums(n - k + 1);
    for(int i = 0; i < n - k + 1; i++) {
        int cur = 0;
        for(int j = i; j < i + k; j++) {
            cur += elements[j];
        }
        sums[i] = cur;
    }

    int xor_sum = 0;
    for(int i : sums) {
        xor_sum ^= i;
    }

    cout << xor_sum << endl;
    return 0;
}

int generate(int n, int x, int a, int b, int c) {
    if(n==1) return x;
    return (a * generate(n-1, x, a, b, c) + b) % c;
}
```


// and this is chatgpt code
```
#include <bits/stdc++.h>
using namespace std;

int generate(int n, int x, int a, int b, int c);

int main() {
    int n, k, x, a, b, c;

    if (!(cin >> n >> k >> x >> a >> b >> c)) {
        return 0;
    }

    vector<int> elements(n);

    for (int i = n - 1; i >= 0; i--) {
        elements[i] = generate(i + 1, x, a, b, c);
    }

    vector<int> sums(n - k + 1);

    for (int i = 0; i < n - k + 1; i++) {
        int cur = 0;

        for (int j = i; j < i + k; j++) {
            cur += elements[j];
        }

        sums[i] = cur;
    }

    int xor_sum = 0;

    for (int i : sums) {
        xor_sum ^= i;
    }

    cout << xor_sum << endl;
    return 0;
}

int generate(int n, int x, int a, int b, int c) {
    if (n == 1) return x;
    return (a * generate(n - 1, x, a, b, c) + b) % c;
}
```