# Removing Digits

## Problem

- **Source:** [CSES 1637: Removing Digits](https://cses.fi/problemset/task/1637/)
- **Code:** [`View accepted C++ solution (removingdigits.cpp)`](./removingdigits.cpp)

For an integer $n$, one operation selects any nonzero digit of the current number and subtracts it. Determine the minimum number of operations required to reach zero.

For example, $27\rightarrow20\rightarrow18\rightarrow10\rightarrow9\rightarrow0$ takes five operations.

## Idea

Let $dp[i]$ be the minimum number of operations required to reduce $i$ to zero.

If the current number is $i$ and we select a nonzero digit $d$ from its decimal representation, the next number is $i-d$. Reducing that value optimally takes $dp[i-d]$ additional operations. Therefore,

$$dp[i]=1+\min_{\substack{d\text{ is a nonzero digit of }i}}dp[i-d].$$

The base case is $dp[0]=0$. Every transition produces a smaller number, so states can be evaluated from $1$ through $n$.

## Algorithm

1. Set $dp[0]=0$ and initialize all positive states as unreachable.
2. For every $i=1,2,\ldots,n$:
   * extract all decimal digits of $i$;
   * for every nonzero digit $d$, minimize $dp[i]$ with $dp[i-d]+1$.
3. Output $dp[n]$.

## Correctness

We prove that $dp[i]$ is the minimum number of operations required to reduce $i$ to zero.

Any valid first operation subtracts a nonzero digit $d$ of $i$, leaving $i-d$. After this operation, at least $dp[i-d]$ more operations are required. Thus, every valid strategy has length at least $dp[i-d]+1$ for one of the available digits.

Conversely, for every nonzero digit $d$ of $i$, subtracting $d$ is a valid first operation. Following an optimal strategy from $i-d$ then reaches zero in $dp[i-d]+1$ operations.

Taking the minimum over all valid digits therefore gives exactly the optimum for $i$. Hence, $dp[n]$ is the required answer.

## Implementation

Digits are extracted by repeated division by ten:

```cpp
int x = i;

while (x) {
    int d = x % 10;
    x /= 10;

    if (d) dp[i] = min(dp[i], dp[i - d] + 1);
}
```

Digit zero is ignored because subtracting it would not change the number.

The array is initialized with $n+1$, which is larger than any possible answer. At least one is subtracted per operation, so no more than $n$ operations are needed.

## Complexity

Each number from $1$ through $n$ examines all of its decimal digits. The time complexity is $O(n\log n)$ and the DP array uses $O(n)$ space. Under the constraint $n\le10^6$, each number has at most seven digits.

## Worked Example

For $n=27$,

$$dp[27]=1+\min(dp[25],dp[20]).$$

Choosing digit $7$ gives $27\rightarrow20$. Then subtracting $2$, $8$, $1$, and $9$ gives

$$27\rightarrow20\rightarrow18\rightarrow10\rightarrow9\rightarrow0.$$

Thus, $dp[27]=5$.
