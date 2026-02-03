#include <bits/stdc++.h>
using namespace std;

int fibonacciBasic(int n)
{
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacciBasic(n - 2) + fibonacciBasic(n - 1);
}

int fibonacciMemo(int n)
{
    function<int(int, unordered_map<int, int> &)> _fibonacciMemo;
    _fibonacciMemo = [&](int n, unordered_map<int, int> &memo) -> int
    {
        if (n <= 0)
            return 0;
        if (n == 1)
            return 1;
        if (memo.count(n))
            return memo[n];
        memo[n] = _fibonacciMemo(n - 1, memo) + _fibonacciMemo(n - 2, memo);
        return memo[n];
    };

    unordered_map<int, int> memo;
    return _fibonacciMemo(n, memo);
}

int fibonacciTable(int n)
{
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;

    vector<int> table(n + 1);
    table[1] = 1;

    for (int i = 2; i <= n; i++)
        table[i] = table[i - 1] + table[i - 2];

    return table[n];
}

int main()
{
    cout << "Fibonacci Basic (20): " << fibonacciBasic(20) << endl;
    cout << "Fibonacci Memo (20): " << fibonacciMemo(20) << endl;
    cout << "Fibonacci Table (20): " << fibonacciTable(20) << endl;
    return 0;
}
