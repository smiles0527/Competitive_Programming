//junior 1
B = int(input())
P = 5 * B - 400
print(P)
if P  < 100:
    print(1)
elif P == 100:
    print(0)
else:
    print(-1)

//junior 2
N = int(input())
max_bid = -1

for i in range(N):
    name = input()
    current_bid = int(input())
    if max_bid < current_bid:
        winner = name
        max_bid = current_bid

print(winner)

//junior 3 and junior 4
#include <iostream>
#include <string>
using namespace std;

int main() {
    string code;

    while (true) {
        cin >> code;
        if (code == "99999") break;
        
        int firstDigit = code[0] - "0";
        int secondDigit = code[1] - "0";
        int sum = firstDigit + secondDigit;

        string direction;
        if (sum % 2 == 1) direction = "left";
        elif (sum == 0) direction = ""; 
        else direction = "right";
        
        string steps = code.substr(0, 2);
        if (!direction.empty()) cout << direction << " " << steps << endl;
        else cout << steps << endl; 
    }


    string letters = "LSMLSMLSMLSMLLM";
    int l = 0;
    int m = 0;
    for(int i   = 0; i < letters.size(); i++) {
        if (letters[i] == 'L') l++;
        else m++;
    }

    

}

