#include <bits/stdc++.h>
using namespace std;

/*
We can quickly notice that the total number of C, O, and W has to be even. So, #C = #O = #W = N.
If N = odd, then we can automatically output -1.

If the entire string S itself is a square string: S = Y + Y, then we delete everything at once, M = 1.

When N is even but S is not already square:
- Each letter appears an even number of times.
- You can pair equal letters (C with C, O with O, W with W).
- Each pair forms one character in the first half and one in the second half of a square subsequence.
- All pairs can always be split into two square subsequences.

So min(operations) = 2.

What the output means:
e.g. 1 1 1 2 2 2 
--> Characters 1-3 deleted in operation 1
--> Characters 4-6 deleted in operation 2   
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, k;
    cin >> T >> k;

    while (T--) {
        int N;
        string S;
        cin >> N >> S;
        int L = 3 * N;

        //impossible case
        if (N % 2 == 1) {
            cout << -1 << "\n";
            continue;
        }

        //check if one operation is enough
        int half = L / 2;
        if (S.substr(0, half) == S.substr(half)) {
            cout << 1 << "\n";
            //if it passes, whole string is a square already
            for (int i = 0; i < L; i++) {
                // M = 1, every character gets 1
                cout << 1 << (i + 1 == L ? '\n' : ' ');
            }
            continue;
        }
        
        //otherwise, we can always do it in 2 operations
        //we essentially want to pair up the characters

        int m = N / 2;
        //write down all positions of characters
        vector<int> posC, posO, posW;
        posC.reserve(N);
        posO.reserve(N);
        posW.reserve(N);

        for (int i = 0; i < L; i++) {
            if (S[i] == 'C') posC.push_back(i);
            else if (S[i] == 'O') posO.push_back(i);
            else posW.push_back(i);
        }

        //pair them like this:
        // 1st with (1+N/2)th
        // 2nd with (2+N/2)th
        // ...
        // (N/2)th with (N/2+1)th
        // this way, every letter belongs to exactly one pair, each pair has equal letters
        vector<int> mate(L, -1); //mate[i] is the index of the character paired with character at index i

        // add all pairs to mate vector (we can do this in O(N) time) 
        auto add_pairs = [&](const vector<int>& v) {
            for (int i = 0; i < m; i++) {
                // add pair (i, i+m) to mate vector (i+m is the index of the character paired with i) 
                int a = v[i], b = v[i + m];
                // if a == b, then we can't pair them because they're the same character (we'll pair them later) 
                mate[a] = b;
                mate[b] = a;
            }
        };

        // add pairs for C, O, and W
        add_pairs(posC);
        add_pairs(posO);
        add_pairs(posW);

        //turn pairs into square subsequences
        //for each pair, one position is earlier in the string than the other. call them left and right
        //if we pick several pairs in increasing order of left, and their right is also increasing
            //left position forms the first half
            //right position forms the second half
            //this is a square subsequence
        vector<int> lefts;
        lefts.reserve(3 * m);
        for (int i = 0; i < L; i++) {
            // if i is a pair, then i is the left position of the pair and mate[i] is the right position 
            if (mate[i] != -1 && i < mate[i]) lefts.push_back(i);
        }

        //now, we can delete the characters in the first half of the square subsequence in operation 1 
        //and the characters in the second half of the square subsequence in operation 2
        //we can do this because we know that the characters in the first half of the square subsequence
        //are the characters that are in the same position in the original string as the characters in the
        //second half of the square subsequence
        vector<int> ans(L, 0);
        int last1 = -1, last2 = -1;

        for (int lpos : lefts) {
            int rpos = mate[lpos];

            int take = -1; //take = -1 means that we don't delete anything
            bool ok1 = (rpos > last1); 
            bool ok2 = (rpos > last2);

            if (ok1 && ok2) {
                take = (last1 > last2 ? 1 : 2); //if both ok1, ok2 are true, then we can delete either 1 or 2 characters
            } else if (ok1) {
                take = 1;
            } else {
                take = 2;
            }

            //update last1 and last2
            if (take == 1) last1 = rpos;
            else last2 = rpos;

            ans[lpos] = take;
            ans[rpos] = take;
        }

        cout << 2 << "\n"; //we can always do it in 2 operations    
        for (int i = 0; i < L; i++) {
            cout << ans[i] << (i + 1 == L ? '\n' : ' ');
        }
    }

    return 0;
}
// time complexity: O(N^2)
// space complexity: O(N)