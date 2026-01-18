#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int z = 0; z < t; z++)
    {
        int n, k;
        cin >> n >> k;
        string r;
        cin >> r;

        if (k == n)
        {
            if (r[0] == '0')
            {
                if (n%2 == 0)
                {
                    cout << 0 << " " << n << "\n";
                }
                else
                {
                    cout << 0 << " " << n-1 << "\n";
                }
            }
            else
            {
                if (n%2 == 1)
                {
                    cout << 1 << " " << n << "\n";
                }
                else
                {
                    cout << 1 << " " << n-1 << "\n";
                }
            }
            continue;
        }
        vector<int> arr(n, -1);

        for (int i = 0; i + k < n; i++)
        {
            if (arr[i] == -1)
            {
                arr[i] = 0;
            }
            int a = arr[i];
            int b = r[i] - '0';
            int c = r[i + 1] - '0';

            if ((a+b+c)%2 == 0)
            {
                arr[i+k] = 0;
            }
            else
            {
                arr[i+k] = 1;
            }
        }

        int min = 0;
        int max = 0;

        for (int i = 0; i < k; i += k)
        {
            int c1 = 0;
            int c2 = 0;

            for (int j = i; j < n; j += k)
            {
                int temp;
                if (arr[j] == -1)
                {
                    temp = 0;
                }
                else
                {
                    temp = arr[j];
                }
                c1 += temp;

                if (temp == 0)
                {
                    c2 += 1;
                }
            }
            if (c1 < c2)
            {
                min += c1;
                max += c2;
            }
            else
            {
                min += c1;
                max += c2;
            }
        }
        cout << min << " " << max << "\n";
    }
}