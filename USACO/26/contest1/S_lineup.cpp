#include <bits/stdc++.h>
using namespace std;
/*
Every second, three things happen:
- Cow at pos 0 jumps to position floor(t/2)
    - Any cow at a position greater that floor(t/2) does not move
    - Any cow at a position less than or equal to t/2 gets moved forward

- Because of this, all cows at positions > floor(t/2) move one step forward
- A new cow joins the end of line

This is solvable using a simulation approach, except t goes to 1e18, making direct simulation far too slow.

To not move, your position must be greater than the jump spot. So, if you are cow C, c > t/2. Algebraically,
this is identical to t < 2c. 

The drift starts safe at position c until t = 2c. At t = 2c, the cow is at position c. From this moment on,
the cow moves 1 step closer to 0 every single second (as it's in the "danger zone")
- this can be calculated by using Current Position = (Starting Position) - (Time passed since moving started)

Position = c - (t - 2c) - 1  <-- -1 is needed because the shift happens AT t=2c
Position = 3c - t - 1

After the cow hits position 0, they end up in a loop:
- it jumps from 0 to the middle
- it slides back down to 0
- repeat
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    if (cin >> Q) {

        while (Q--) {
            long long type, val, t;
            cin >> type >> val >> t;

            //type 1: given time t, find position of cow val
            if (type == 1){
                long long c = val;
                
                //casework on which segment cow c is in at time t
                if (t < 2 * c) cout << c << "\n"; //formula comes from derivation above          
                else if (t < 3 * c - 1) cout << 3 * c - t - 1 << "\n";    
                else{
                    //cow position is 0 here
                    long long cur = 3 * c - 1, ans = 0;

                    while (cur < t){
                        long long jmp_t = cur + 1; //jump happens next second
                        long long p = jmp_t / 2; //position after jump (the middle)
                        long long end = jmp_t + p; //time when cow returns to 0 (Time + Distance)

                        // Case A: target time 't' is inside the cycle
                        if (end > t){
                            //stop here and calculate position
                            if (t == jmp_t) ans = p; //is it exactly at jump?
                            else ans = p - (t - jmp_t); //sliding back?
                            cur = t + 1; //break loop
                        // Case B: target time 't' is in future 
                        } else{ 
                            //cycle finishes before our target time, skip
                            cur = end; 
                        }
                    }
                    cout << (cur == t ? 0 : ans) << "\n";
                }
            //type 2: given time t, find which cow is at position val
            } else{
                long long x = val; //position
                //reverse the process above to find which cow is at position x at time t
                while (true) {
                    if (x == t) { cout << x << "\n"; break; } //cow at position x is the new cow
                    //check if cow is in the drifting phase 
                    //if the cow is here now, it must have started here at the beginning, must be cow X
                    long long h = t / 2;
                    if (x > h) { cout << x << "\n"; break; }
                    
                    //cow is in the middle
                    if (x == h) { 
                        x = 0; 
                        t--; 
                    } else {
                        // slightly adjusted ceiling formula for better precision: (t - 2x + 2)/3
                        long long k = (t - 2 * x) / 3; //time spent drifting + 1
                        if (k < 1) k = 1; //at least 1 second
                        t -= k; 
                        x += k;
                    }
                }
            }
        }
    }
    return 0;
}
//Time complexity: O(Q log T) where T is the maximum time value (1e18)
//Space complexity: O(1)