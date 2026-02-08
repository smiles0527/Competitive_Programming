#include <bits/stdc++.h>
using namespace std;

int main() {

    string line;
    while (getline(cin, line))
    {
        if (line == "0"){
            break;
        }

        vector<string> uwu;
        string cur = "";

        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ' ') {
                if (!cur.empty()) {
                    uwu.push_back(cur);
                    cur.clear();
                }
            } else {
                cur.push_back(line[i]);
            }
        }
        if (!cur.empty()) uwu.push_back(cur);

        vector<string> st;

        for (int i = uwu.size() - 1; i >= 0; i--) {
            string t = uwu[i];
            if (t == "+" || t == "-") {
                string a = st.back(); st.pop_back();
                string b = st.back(); st.pop_back();
                st.push_back(a + " " + b + " " + t);
            } else {
                st.push_back(t);
            }
        }

        cout << st.back() << "\n";
    }
}
