#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    string line;

    cin >> n;
    getline(cin, line);

    map<string, vector<string>> idk;


    for (int i = 0; i < n; i++){
        string from;
        getline(cin, from);

        while (getline(cin, line)){
            string key = "<A HREF=\"";
            int pos = 0;

            while (true){
                int start = line.find(key,pos);
                if (start == -1){
                    break;
                }

                start += key.size();
                int end = line.find('"', start);
                if (end == -1){
                    break;
                }

                string to = line.substr(start, end - start);

                cout << "Link from " << from << " to " << to << "\n";
                idk[from].push_back(to);

                pos = end + 1;
            }

            if (line == "</HTML>"){
                break;
            }
        }
    }

    while (true){
        string start;
        getline(cin, start);

        string target;
        getline(cin, target);

        if (start == "The End"){
            break;
        }
        
        queue<string> q;
        map<string, bool> visited;

        q.push(start);
        visited[start] = true;

        bool smth = false;

        while(!q.empty()){
            string cur = q.front();
            q.pop();

            if (cur == target){
                smth = true;
                break;
            }

            for (string next : idk[cur]){
                if (!visited[next]){
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        if (smth){
            cout << "Can surf from " << start << " to " << target << ".\n";
        }
        else {
            cout << "Can't surf from " << start << " to " << target << ".\n";
        }
    }

    return 0;
    
}