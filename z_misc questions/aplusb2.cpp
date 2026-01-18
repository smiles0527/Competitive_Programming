#include <iostream>
#include <string>
#include <algorithm>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    while(N--){
        std::string A, B;
        std::cin >> A >> B;

        int i = A.size() - 1;
        int j = B.size() - 1;
        int carry = 0;
        std::string R;

        while(i >= 0 || j >= 0 || carry){
            int sum = carry;
            if(i >= 0) sum += A[i--] - '0';
            if(j >= 0) sum += B[j--] - '0';
            R.push_back(char('0' + sum % 10));
            carry = sum / 10;
        }

        std::reverse(R.begin(), R.end());
        std::cout << R << "\n";
    }

    return 0;
}
