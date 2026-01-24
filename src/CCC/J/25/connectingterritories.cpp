#include <bits/stdc++.h>
using namespace std;

int main(){
    int R, C, M;
    cin >> R >> C >> M;              // read number of rows, columns, and max tile cost

    vector<int> prev(C), cur(C);     // prev holds min costs for previous row, cur for current row
    int count = 0;                   // running counter to generate tile cotss in rowmajor order

    // initialize first row costs
    for(int j = 0; j < C; j++){
        count++;                     // move to next tile index
        if (count > M) count = 1;   // wrap around after reaching M
        prev[j] = count;            // store cost of tile (0, j)
    }

    // process rows 1 through R-1
    for(int r = 1; r < R; r++){
        for(int j = 0; j < C; j++){
            count++;                 // advance counter for next tile
            if (count > M) count = 1; // wrap around cost
            int cost = count;       // cost of tile (r, j)

            // find best path to this tile from previous row
            int best = prev[j];     // directly above
            if (j > 0)     best = min(best, prev[j-1]); // above-left
            if (j+1 < C)  best = min(best, prev[j+1]); // above-right

            cur[j] = best + cost;   // total cost to reach (r, j)
        }
        prev.swap(cur);             // make current row the "previous" for next iteration
    }

    // after last row, the smallest entry in prev is min path cost to bottom
    sort(prev.begin(), prev.end()); 
    cout << prev[0];                // output minimum connecting path cost
    return 0;                       // end program
}
