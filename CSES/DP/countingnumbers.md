# Counting Numbers

## Problem

- **Source:** [CSES 2220: Counting Numbers](https://cses.fi/problemset/task/2220/)
- **Code:** [`View accepted C++ solution (countingnumbers.cpp)`](./countingnumbers.cpp)

Count the integers in the interval $[a,b]$ whose decimal representations contain no two equal adjacent digits.

For example, $121$ is valid, while $122$ is not because its final two digits are equal.

## Idea

Checking every integer is impossible because $b\le 10^{18}$.

Define $\operatorname{calc}(x)$ as the number of valid integers between $0$ and $x$. Then the answer is

$$\operatorname{calc}(b)-\operatorname{calc}(a-1).$$

To calculate $\operatorname{calc}(x)$, build the number one digit at a time while ensuring that its prefix does not exceed the corresponding prefix of $x$.

## Digit DP State

Let $f(p,\text{prev},\text{tight})$ be the number of valid ways to choose digits starting from position $p$.

The state stores:

* $p$: the current digit position;
* `prev`: the previous actual digit;
* `tight`: whether the digits chosen so far are equal to the prefix of $x$.

If `tight` is true, the current digit cannot exceed the corresponding digit of $x$. Otherwise, any digit from $0$ to $9$ is allowed.

A special value $\text{prev}=10$ represents that the number has not started yet. Initial zeroes are only padding and should not be treated as adjacent digits. For example, the integer $7$ is represented as $000\ldots007$, and the leading zeroes must not make it invalid.

## Transition

At position $p$, try every digit $d$ allowed by the upper bound. If the number has already started and $d=\text{prev}$, the choice is invalid because it creates equal adjacent digits.

Otherwise, continue to the next position. If `prev` is $10$ and $d=0$, the number still has not started, so the next previous value remains $10$. In every other case, the next previous value is $d$.

When all positions have been processed, one valid integer has been constructed.

## Algorithm

1. Implement `calc(x)` using digit DP.
2. Convert $x$ into a string of digits.
3. Begin at position $0$, with no previous digit and a tight prefix.
4. Try every valid next digit.
5. Memoize states whose prefix is already smaller than $x$.
6. Return $\operatorname{calc}(b)-\operatorname{calc}(a-1)$.

## Correctness

We prove that `calc(x)` counts exactly the valid integers from $0$ to $x$.

Every integer in this range has a unique representation using the same number of digits as $x$, possibly with leading zeroes.

The `tight` state ensures that the constructed digit sequence never exceeds $x$. Therefore, every counted representation corresponds to an integer at most $x$.

The transition rejects a digit exactly when it equals the previous actual digit. Leading zeroes use the special value $10$, so they are ignored until the first nonzero digit is selected.

Thus, a representation is accepted exactly when its integer has no equal adjacent digits. Every integer from $0$ to $x$ has one representation, so every valid integer is counted exactly once. Therefore, `calc(x)` is correct.

Finally, subtracting `calc(a - 1)` removes all valid integers smaller than $a$, leaving exactly the valid integers in $[a,b]$.

## Implementation

The memoization table stores only states with `tight = false`. When `tight` is true, the state depends on the exact prefix of $x$, so it is evaluated directly. There are only as many tight states as there are digit positions.

The special previous value $10$ distinguishes leading zeroes from actual digit zeroes. This is necessary because $100$ must be rejected, while the padded representation of $7$ must remain valid.

The answer fits in `long long`, since there are at most $10^{18}+1$ integers in the complete range.

## Complexity

Let $L$ be the number of digits of $x$. There are $L$ positions and $11$ possible previous-digit states. Each state tries at most $10$ digits.

The time complexity of one call to `calc` is $O(L\cdot11\cdot10)$. Since $L\le19$, this is effectively constant. The memory complexity is $O(L\cdot11)$.

## Worked Example

Consider the interval $[10,25]$. There are $16$ integers in this interval. The invalid numbers are $11$ and $22$, because each contains two equal adjacent digits.

All other numbers are valid, so the answer is $16-2=14$.
