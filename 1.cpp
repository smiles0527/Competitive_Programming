#include <bits/stdc++.h>
using namespace std;

/*
Core idea: binary search for the worst final A, and then check if it's >= fA.

This question gives us 5 values: A, B, cA, cB, fA. We're starting with A, and B. We know that we can take cB of B chips 
and we can convert that cB chips into cA A chips. 

We need to find a value x, denoting random chips that are given to us randomly. Now, this x value can both contain A chips
and B chips, but we don't know. This x value satisfies that we can guarantee having at least fA A chips after the conversion.

This value x can give us a few A chips, but if we won't have enough, we'll have to turn to our B chips, Using our cB - cA 
conversion, we can convert that B chips into A chips. And we keep repeating this until we reach our fA A chips. 

Since the question is asking for the mimimum value of x, we know that the distribution of A and B chips will be in the 
worst-case possible, meaning that we'll receive a number of B chips that lacks one singular chip to make an additional conversion
and give us as least A chips as possible. 

Intuitively, we can just guess any random value x within the constraints (1 to 10^18) and check if that x value can g
uarantee us at least fA A chips. We can guess a huge number of x. If that number x works, every number greater than x
will work. If the number x doesn't work, we will have to guess a smaller number. 

So, we can use binary search to find the minimum value of x that works. (This is the most efficient way to do this given
the extreme constraints of x being up to 10^18).

-CW
*/

using ll = long long;
using i128 = __int128_t; //128 bit integer type to avoid overflows
//note that __int128_t is a gcc extension and may not be supported by all compilers, you'll have to compile with GNU C++11 
//or a C++11 compiler that supports __int128_t. MSVC doesn't support it (standard VSC)
//USACO grading servers support __int128_t

i128 getA(i128 t, ll cA, ll cB) {
    /*
    This function returns the number of A chips after t chips are added to the system. 

    After obtaining t chips, we convert as many B chips to A chips as possible using the conversion rate cB/cA.
    So we compute t/cB, giving us the maximum number of A chips we can obtain from the t chips. t/cB in c++ is
    directly computed as a floor division, so we won't worry about the leftover B chips. Since we can perform
    our conversion t/cB times, we will obtain (t/cB) * cA A chips, as each conversion will give us cA A chips.

    Finally, we subtract t from the total A chips obtained, since t chips were added to the system.
    */
    return (i128)cA * (t / (i128)cB) - t;
}

//Binary search for the worst final A
bool ok(ll A, ll B, ll cA, ll cB, ll fA, ll x) {
    i128 minB = (i128)B; //min number of B chips we can have
    i128 maxB= (i128)B + (i128)x; //max number of B chips we can have

    //floor division values for cA and cB
    i128 qminB = minB / (i128)cB; //gives us the number of conversions we can do with minB
    i128 qmaxB = maxB / (i128)cB; //gives us the number of conversions we can do with maxB

    i128 t1 = qminB * (i128)cB + ((i128)cB - 1); //t1 is the number of B chips we can convert with 1 conversion
    if (t1 > maxB) t1 = maxB; //if t1 is greater than maxB, we'll have to use maxB
                                //this is because we can't convert more B chips than we can theoretically have

    i128 Achips = getA(t1, cA, cB); //Achips is the minimum number of A chips we can obtain with t1 B chips
                                  //we can convert with 1 conversion.
                                  
    Achips = min(Achips, getA(maxB, cA, cB)); //check the case where we have maxB B chips
                                          //if line 60 is true, we can obtain at least fA A chips

    //check if we can obtain at least fA A chips with the conversions we can do with qminB B chips
    if (qminB + 1 <= qmaxB - 1) { //if there's at least one more conversion we can do between qminB and qmaxB
        i128 qMid; //qMid is the number of conversions we can do with qminB B chips
        if (cA < cB) qMid = qmaxB - 1; //because 
        else qMid = qminB + 1; //if not, we can convert qminB B chips into A chips
        i128 t3 = qMid * (i128)cB + ((i128)cB - 1); //t3 is the number of B chips we can convert with qMid conversions
        Achips = min(Achips, getA(t3, cA, cB)); //check if we can obtain at least fA A chips with t3 B chips
    }

    //finally, check the case where we have minB B chips
    i128 Atotal = (i128)A + (i128)B + (i128)x + Achips; //Atotal is the total number of A chips we can obtain
    //formula above can be obtained from rearranging the equation (t/cB) * cA = t - B + A
    return Atotal>= (i128)fA;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll A, B, cA, cB, fA;
        cin >> A >> B >> cA >> cB >> fA;

        //binary search for the worst final A
        ll lo = 0, hi = (ll)1e18;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            //recursive call to check if it's >= fA
            if (ok(A, B, cA, cB, fA, mid)) hi = mid; 
            else lo = mid + 1;
        }
        cout << lo << "\n"; //returning lo because lo == hi means that we can obtain at least fA A chips
    }
    return 0;
}
// time complexity: O(log(fA))
// space complexity: O(1)