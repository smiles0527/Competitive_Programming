#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> ppl(n);

    for (int i = 0; i < n; i++){
        cin >> ppl[i];
    }

    int idk = n/2;

    int count = 0;
    for (int i = 0; i < ppl.size()/2; i++){
        if (ppl[i] / ppl[i+idk] == 1 && ppl[i] % ppl[i+idk] == 0){
            count++;
        }
    }
    for(int i = 0; i < n; i++) 
        if(ppl[i] = ppl[(i+idk)%n]) count+=2;

    cout << count;
}