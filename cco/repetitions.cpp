#include <iostream>
#include <string>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n;
    cin >> n;
    char current;
    int count, answer = 0;
    for(int i = 0; i < size(n); i++){
        if(n[i] != current){
            current = n[i];
            count = 0;
        }
        if(n[i] == current){
            count++;
        }
        answer = max(answer, count);
    }
    cout << answer;
}