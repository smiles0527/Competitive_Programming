#include <bits/stdc++.h>
using namespace std;
int main(){
    string table;
    cin >> table;
    int table_size = table.size();
    table += table;
    int countA = 0; 
    int countB = 0; 
    int countC = 0;
    for (int i = 0; i < table_size; i++){
        if (table[i] == 'A') countA++;
        else if (table[i] == 'B') countB++;
        else countC++;
    }
    map<char, int> sectionA;
    map<char, int> sectionB;
    map<char, int> sectionC;
    sectionA['A'] = 0, sectionA['B'] = 0, sectionA['C'] = 0;
    sectionB['A'] = 0, sectionB['B'] = 0, sectionB['C'] = 0;
    sectionC['A'] = 0, sectionC['B'] = 0, sectionC['C'] = 0;
    for (int i = 0; i < countA; i++) sectionA[table[i]]++;
    for (int i = countA; i < countA + countB; i++) sectionB[table[i]]++;
    for (int i = countA + countB; i < countA + countB + countC; i++) sectionC[table[i]]++;
    int num_of_swaps = sectionA['B'] + sectionA['C'] + sectionB['A'] + sectionB['C'] - min(sectionA['B'], sectionB['A']);
    set<int> swaps; 
    swaps.insert(num_of_swaps);
    for (int i = 0; i < table_size - 1; i++){
        sectionA[table[i]]--; //Remove first part of section A
        sectionA[table[i + countA]]++; //Add to section A
        sectionB[table[i + countA]]--; //Remove first part of section B
        sectionB[table[i + countA + countB]]++; //Add to section B
        sectionC[table[i + countA + countB]]--; //Remove first part of section C
        sectionC[table[i + countA + countB + countC]]++; //Add to section C
        num_of_swaps = sectionA['B'] + sectionA['C'] + sectionB['A'] + sectionB['C'] - std::min(sectionA['B'], sectionB['A']);
        swaps.insert(num_of_swaps);
    }
    sectionA['A'] = 0, sectionA['B'] = 0, sectionA['C'] = 0;
    sectionB['A'] = 0, sectionB['B'] = 0, sectionB['C'] = 0;
    sectionC['A'] = 0, sectionC['B'] = 0, sectionC['C'] = 0;
    //Count frequencies once more, except in CBA order now
    for (int i = 0; i < countC; i++) sectionC[table[i]]++;
    for (int i = countC; i < countC + countB; i++) sectionB[table[i]]++;
    for (int i = countC + countB; i < countC + countB + countA; i++) sectionA[table[i]]++;
    num_of_swaps = sectionA['B'] + sectionA['C'] + sectionB['A'] + sectionB['C'] - std::min(sectionA['B'], sectionB['A']);
    swaps.insert(num_of_swaps);
    for (int i = 0; i < table_size - 1; i++){
        sectionC[table[i]]--; //Remove first part of section C
        sectionC[table[i + countC]]++; //Add to section C
        sectionB[table[i + countC]]--; //Remove first part of section B
        sectionB[table[i + countC + countB]]++; //Add to section B
        sectionA[table[i + countC + countB]]--; //Remove first part of section A
        sectionA[table[i + countC + countB + countA]]++; //Add to section A
        num_of_swaps = sectionA['B'] + sectionA['C'] + sectionB['A'] + sectionB['C'] - std::min(sectionA['B'], sectionB['A']);
        swaps.insert(num_of_swaps);

    }
    cout << *swaps.begin();
    return 0;
}