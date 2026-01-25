#include <bits/stdc++.h>
using namespace std;

long long type2(long long x, long long t)
{
    while (t > 0)
    {
        if (x == t) return t;
        if (x > t / 2) return x;

        long long m = t - 2*x;
        
        if (m <= 1)
        {
            x = 0;
            t--;
            continue;
        }

        long long k = (m-2)/3 + 1;
        x += k;
        t -= k;
    }
    return 0;
}

long long type1(long long c, long long t)
{
    long long cur = c;
    long long p = c;
    
    while (cur < t)
    {
        long long next = cur + 1;
        long long nc = next / 2;

        if (p > nc)
        {
            long long jump = min(t, 2*p-1);
            cur = jump;
            continue;
        }

        if (p == 0)
        {
            p = nc;
            cur = next;
            continue;
        }

        long long k = min(p, t - cur);
        p -= k;
        cur += k;
    }
    return p;
}

int main()
{
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        long long type, a, b;
        cin >> type >> a >> b;
        if (type == 1)
        {
            cout << type1(a,b) << "\n";
        }
        else
        {
            cout << type2(a,b) << "\n";
        }
    }
}