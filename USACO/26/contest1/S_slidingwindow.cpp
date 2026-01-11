#include <bits/stdc++.h>
using namespace std;

/*
Imagine a row of light switches (the hidden binary string b). Some are ON (1) and some are OFF (0). We cannot see them.
We're given a clue sheet (r), made by sliding a window of size K over the switches. At each step, the sheet records:
- 0 if the number of ON switches in the window is even.
- 1 if the number of ON switches in the window is odd.
We need to figure the minimum and maximum possible number of ON switches in the entire row, consistent with the clue sheet.

The key lies in recognizing that the row can be decomposed into K independent chains of switches. Imagine the window covers
switches 1, 2, and 3 (k = 3). Now slide it to the right. It covers 2, 3, 4.
Note that the switches 2 and 3 didn't move. They are in both windows.
- the only thing that changed is 1 left, 4 entered.
- if the even/odd status changed, then switch 4 must be different from switch 1.
- if the status stayed the same, then switch 4 must be the same as switch 1.
This then creates a chain reaction: if we guess the state for switch 1, the clue sheet forces the setting for switch 4,
which then forces switch 7, and so on.

We break this down into K chains because the rule links switches K steps apart.
- Chain A: switches 1, 1+K, 1+2K, ...
- Chain B: switches 2, 2+K, 2+2K, ...
- Chain C: switches 3, 3+K, 3+2K, ...
We need to maintain the best choice for each chain. We have two options for each chain:
- Option A: assume the first switch in the chain is OFF (0). Count how many ON (1) switches this implies in the chain (c0).
- Option B: assume the first switch in the chain is ON (1). Count how many ON (1) switches this implies in the chain (c1).
Pick the option that gives the result we want (smallest or largest total number of ON switches).

There is one final rule: the very first clue (r_0) told us that if the first window had an even or odd number of 1s. After
we pick the best options for all chains, we check if our choices match this rule. 
- if they match, we are done.
- if they don't match, we broke the rule. We must flip exactly one chain to fix the even/odd count. To keep our answer
  optimal, we pick the chain that changes our total count the least.


*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            int n, k;
            cin >> n >> k;
            string r;
            cin >> r;

            // 'base' tracks the total ones if every chain starts with 0.
            // 'mn' tracks the minimum cost (absolute difference) to flip a chain's decision.
            long long base = 0;
            int mn = 1e9;
            
            // Stores the difference (ones_if_1 - ones_if_0) for each chain.
            vector<int> df; 
            df.reserve(k);

            // Decompose the string into K independent chains
            for (int j = 0; j < k; ++j) {
                int c0 = 0; // Count of ones if this chain starts with 0
                int cur = 0; // Current bit value in the chain (assuming start is 0)

                // Iterate through the chain: j, j+K, j+2K...
                for (int i = j; i < n; i += k) {
                    if (cur) c0++;
                    
                    // Use recurrence: b[i+K] = b[i] ^ r[i] ^ r[i+1]
                    // We only compute next state if i+K is within bounds
                    if (i + k < n) {
                        cur ^= (r[i] - '0') ^ (r[i+1] - '0');
                    }
                }

                // If chain starts with 1, all bits flip. c1 is just length - c0.
                int len = (n - 1 - j) / k + 1;
                int c1 = len - c0;
                
                base += c0;
                int d = c1 - c0; // Cost difference to flip this chain's start to 1
                df.push_back(d);
                if (abs(d) < mn) mn = abs(d);
            }

            int req = r[0] - '0'; // Required global parity (sum of starts % 2)

            //Calculate Minimum
            long long v_min = base;
            int p = 0; // Parity tracker
            for (int d : df) {
                // Greedily take negative differences to reduce sum
                if (d < 0) {
                    v_min += d;
                    p ^= 1;
                }
            }
            // If parity doesn't match, we must pay the smallest penalty (add |diff|)
            if (p != req) v_min += mn;

            // --- Calculate Maximum ---
            long long v_max = base;
            p = 0;
            for (int d : df) {
                // Greedily take positive differences to increase sum
                if (d > 0) {
                    v_max += d;
                    p ^= 1;
                }
            }
            // If parity doesn't match, pay penalty (subtract |diff| from max)
            if (p != req) v_max -= mn;

            cout << v_min << " " << v_max << "\n";
        }
    }
    return 0;
}
// Time complexity: O(T * (N/K + K)) where T is number of test cases, N is length of string, K is window size
// Space complexity: O(K) for storing differences per chain