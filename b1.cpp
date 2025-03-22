#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<char>> game(n, vector<char>(n));

    for (int i = 0; i < n; i++)
    {
        string line;
        cin >> line;
        for (int j = 0; j <= i; j++)
        {
            game[i][j] = line[j];

            if (game[i][j] == 'W')
            {
                game[j][i] = 'L';
            }
            else if (game[i][j] == 'L')
            {
                game[j][i] = 'W';
            }
            else
            {
                game[j][i] = 'D';
            }
        }
    }

    vector<int> results(m);

    for (int move = 0; move < m; move++)
    {
        int s1, s2;
        cin >> s1 >> s2;
        s1--;
        s2--;

        int count = 0;

        for (int l = 0; l < n; l++)
        {
            for (int r = 0; r < n; r++)
            {
                if ((game[l][s1] == 'W' && game[l][s2] == 'W') ||
                    (game[r][s1] == 'W' && game[r][s2] == 'W'))
                {
                    count++;
                }
            }
        }

        results[move] = count;
    }

    for (int i = 0; i < m; i++)
    {
        cout << results[i] << endl;
    }

    return 0;
}
