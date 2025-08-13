    #include <bits/stdc++.h>
    using namespace std;

    int main() {
        int n;
        cin >> n;
        cin.ignore(); 
        
        for (int i = 0; i < n; i++) {
            string code;
            getline(cin, code);
            string uppercase = "";
            int sum = 0;

            string currentNum = "";
            bool isNegative = false;

            for (int j = 0; j < code.length(); j++) {
                char c = code[j];
            
                if (isupper(c)) {
                    uppercase += c;
                }
            
                if (c == '-' && j + 1 < code.length() && isdigit(code[j + 1])) {
                    isNegative = true;
                }
                else if (isdigit(c)) {
                    currentNum += c;
                    if (j + 1 == code.length() || !isdigit(code[j + 1])) {
                        int val = stoi(currentNum);
                        sum += isNegative ? -val : val;
                        currentNum.clear();
                        isNegative = false;
                    }
                }
            }
            
            
            if (!currentNum.empty()) {
                if (isNegative) {
                    sum -= stoi(currentNum);
                } else {
                    sum += stoi(currentNum);
                }
            }
            
            cout << uppercase << sum << endl;
        }
        
        return 0;
    }