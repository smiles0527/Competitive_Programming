#include <bits/stdc++.h>
using namespace std;
/*
The field is a N x N grid. A picture is fixed size K x K square.
Each picture has a sum of values inside it. After every update, we must output the largest such sum.

We must find the heaviest square among all K x K squares.

Key observation: when one cow increases, only the pictures containing that cow change

Step 1: how many pictures contain one cow?
A cow is at position (r, c).
A K x K picture contains it if:
- its top-left corner is somewhere above and to the left
- but not too far.
There are at most 25^2 = 625 such pictures.

Step 2: keep the sum of every picture
Predefine all possible K x K pictures
There are (N - K + 1)^2 of them.
For each picture, store its current sum 

Step 3: process one update
Suppose a cow at (r, c) changes by d
- find all pictures that include (r, c)
- add d to its closed sum

Step 4: how do we get the maximum sum efficiently/fast?
We need the maximum picture sum after every update.
Instead of scanning all pictures every time
- split picture sums into blocks
- for each block, remember its maximum
- when a picture increases, update its block's maximum
- to get the global answer, scan only the block maxima
This is fast because only increases happen and blocks are few

Per update, update at most 625 pictures, check about 500 block maxima

Worst-case total work: Q * (625 + 500) <= 3 x 10^4 x 1125, well within limits.

-CW
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    int Q;
    cin >> Q;

    //number of K x K squares 
    int n2 = N - K + 1; //number of K x K squares along one dimension
    int M = n2 * n2; //total number of K x K squares

    const int B = 512; //block size
    int nb = (M + B - 1) / B; //number of blocks 

    //sum of each K x K square 
    vector<long long> s(M, 0); //s[i] = sum of values in K x K square i
    vector<long long> mx(nb, 0); //mx[b] = maximum sum in block b

    vector<int> a(N * N, 0); //a[i] = value at cell i

    //function to get cell id from (r, c)
    auto id_cell = [&](int r, int c) {
        //computes the id of the cell at (r, c)
        return (r - 1) * N + (c - 1);
    };
    
    auto id_sq = [&](int i, int j) {
        //computes the id of the K x K square whose top-left corner is at (i, j)
        return (i - 1) * n2 + (j - 1);
    };

    //process queries 
    for (int qq = 0; qq < Q; qq++) {
        int r, c, v;
        cin >> r >> c >> v;

        //update the value at (r, c)
        int &cur = a[id_cell(r, c)];
        long long d = (long long)v - cur; //d = change in value
        cur = v;

        //update all K x K squares containing (r, c) 
        int i1 = max(1, r - K + 1);
        int i2 = min(n2, r);
        int j1 = max(1, c - K + 1);
        int j2 = min(n2, c);

        //update all squares with top-left corner in [i1, i2] x [j1, j2]
        for (int i = i1; i <= i2; i++) {
            int base = (i - 1) * n2; //base index for row i
            for (int j = j1; j <= j2; j++) {
                int idx = base + (j - 1); //index of K x K square with top-left corner at (i, j)
                s[idx] += d; //update sum of this square
                int b = idx / B; //block number
                if (s[idx] > mx[b]) mx[b] = s[idx]; //update block maximum if needed
            }
        }

        long long ans = 0;
        for (int b = 0; b < nb; b++) ans = max(ans, mx[b]);
        cout << ans << "\n";
    }

    return 0;
}
// time complexity: O(N^2 * Q)
// space complexity: O(N^2)