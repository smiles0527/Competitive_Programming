# Palindrome Reorder

## Problem

- **Source:** [CSES 1755: Palindrome Reorder](https://cses.fi/problemset/task/1755/)
- **Code:** [`View accepted C++ solution (palindromereorder.cpp)`](./palindromereorder.cpp)
- **Limits:** string length at most $10^6$, using letters `A` through `Z`.

Rearrange all characters into a palindrome, or report that this is impossible.

## Construction

Characters located anywhere other than the central position of a palindrome occur in mirror-image pairs. Therefore, all frequencies must be even, except for at most one odd frequency that can supply the central character. This condition is both necessary and sufficient.

Let $c$ denote the frequency of a letter. Place $\lfloor c/2\rfloor$ copies of each letter on the left side. If $c$ is odd, place one copy in the middle. The right side must be a mirror image of the left side.

### Algorithm

1. Compute the frequencies of the $26$ letters.
2. Form a string `h` from half of each frequency and a string `m` from the letters with odd frequencies.
3. If `m` contains more than one letter, print `NO SOLUTION`. Otherwise, print

   $$
   h+m+\operatorname{reverse}(h).
   $$

## Justification

Two odd frequencies would produce two unpaired characters, but a palindrome has only one central position. Therefore, such an input must be rejected. In every other case, `h` and $\operatorname{reverse}(h)$ together use an even number of each letter, while `m` contains the single permitted leftover letter. The string

$$
h+m+\operatorname{reverse}(h)
$$

uses every input character and reads the same from both directions.

## Implementation

The frequency array has 26 entries. Building `h` in alphabetic order is not required for correctness, but gives a deterministic answer.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, h, m;
    cin >> s;

    int c[26] = {};

    for (char x : s) c[x - 'A']++;

    for (int i = 0; i < 26; i++) {
        if (c[i] % 2) m += char('A' + i);
        h += string(c[i] / 2, char('A' + i));
    }

    if (m.size() > 1) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    string r = h;
    reverse(r.begin(), r.end());
    cout << h << m << r << '\n';


    return 0;
}
```

## Complexity

Counting and constructing take $O(n)$ time and $O(n)$ space for the output strings.

## Example

For `AAAACACBA`, the counts are `A:6`, `B:1`, and `C:2`. The left half can be `AAAC`, the center is `B`, and the reversed half is `CAAA`, producing `AAACBCAAA`.
