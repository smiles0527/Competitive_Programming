#include <bits/stdc++.h>
using namespace std;

int main() {
    int numberOfDays;
    cin >> numberOfDays;
    
    vector<char> weatherSequence(numberOfDays);
    for (int i = 0; i < numberOfDays; i++) {
        cin >> weatherSequence[i];
    }
    vector<int> consecutiveSunnyFromLeft(numberOfDays, 0);
    
    consecutiveSunnyFromLeft[0] = (weatherSequence[0] == 'S') ? 1 : 0;
    
    for (int i = 1; i < numberOfDays; i++) {
        if (weatherSequence[i] == 'S') {
            consecutiveSunnyFromLeft[i] = consecutiveSunnyFromLeft[i - 1] + 1;
        } else {
            consecutiveSunnyFromLeft[i] = 0;
        }
    }
    vector<int> consecutiveSunnyFromRight(numberOfDays, 0);
    consecutiveSunnyFromRight[numberOfDays - 1] = (weatherSequence[numberOfDays - 1] == 'S') ? 1 : 0;
    
    for (int i = numberOfDays - 2; i >= 0; i--) {
        if (weatherSequence[i] == 'S') {
            consecutiveSunnyFromRight[i] = consecutiveSunnyFromRight[i + 1] + 1;
        } else {
            consecutiveSunnyFromRight[i] = 0;
        }
    }
    
    int longestPossibleStreak = 0;
    bool hasPartlyCloudy = false;
    
    for (int i = 0; i < numberOfDays; i++) {
        if (weatherSequence[i] == 'P') {
            hasPartlyCloudy = true;
            
            
            int sunnyDaysBefore = (i > 0) ? consecutiveSunnyFromLeft[i - 1] : 0;
            
            int sunnyDaysAfter = (i < numberOfDays - 1) ? consecutiveSunnyFromRight[i + 1] : 0;
            
            
            int possibleStreak = sunnyDaysBefore + 1 + sunnyDaysAfter;
            longestPossibleStreak = max(longestPossibleStreak, possibleStreak);
        }
    }

    if (!hasPartlyCloudy) {
        longestPossibleStreak = numberOfDays - 1;
    }
   
}