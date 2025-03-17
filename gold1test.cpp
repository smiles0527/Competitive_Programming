#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

struct Frame
{
    int u, idx;
    ll sT, sF;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> a(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> a[i];
    }
    vector<ll> c(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> c[i];
    }
    vector<vector<int>> children(N + 1);
    for (int i = 1; i <= N; i++)
    {
        children[a[i]].push_back(i);
    }
    vector<int> state(N + 1, 0);
    vector<bool> inCycle(N + 1, false);
    vector<vector<int>> cycles;
    for (int i = 1; i <= N; i++)
    {
        if (state[i])
            continue;
        vector<int> path;
        int cur = i;
        while (true)
        {
            state[cur] = 1;
            path.push_back(cur);
            int nxt = a[cur];
            if (!state[nxt])
            {
                cur = nxt;
                continue;
            }
            else if (state[nxt] == 1)
            {
                int idx = 0;
                while (path[idx] != nxt)
                    idx++;
                vector<int> cyc;
                for (int j = idx; j < (int)path.size(); j++)
                {
                    cyc.push_back(path[j]);
                    inCycle[path[j]] = true;
                }
                cycles.push_back(cyc);
                break;
            }
            else
                break;
        }
        for (auto x : path)
            state[x] = 2;
    }
    vector<ll> dpT(N + 1, 0), dpF(N + 1, 0);
    vector<bool> computed(N + 1, false);
    for (int i = 1; i <= N; i++)
    {
        if (!inCycle[i] && !computed[i])
        {
            vector<Frame> st;
            st.reserve(100);
            st.push_back({i, 0, 0, 0});
            while (!st.empty())
            {
                auto &top = st.back();
                int u = top.u;
                if (top.idx < (int)children[u].size())
                {
                    int v = children[u][top.idx];
                    if (inCycle[v])
                    {
                        top.idx++;
                        continue;
                    }
                    if (!computed[v])
                    {
                        st.push_back({v, 0, 0, 0});
                    }
                    else
                    {
                        top.sT += dpT[v];
                        top.sF += dpF[v];
                        top.idx++;
                    }
                }
                else
                {
                    dpT[u] = min(top.sF, c[u] + top.sT);
                    dpF[u] = c[u] + min(top.sF, top.sT);
                    computed[u] = true;
                    st.pop_back();
                    if (!st.empty())
                    {
                        auto &par = st.back();
                        par.sT += dpT[u];
                        par.sF += dpF[u];
                        par.idx++;
                    }
                }
            }
        }
    }
    vector<ll> T0(N + 1, 0), T1(N + 1, 0);
    for (int i = 1; i <= N; i++)
    {
        if (!inCycle[i])
            continue;
        ll sum0 = 0, sum1 = 0;
        for (auto v : children[i])
        {
            if (inCycle[v])
                continue;
            sum0 += dpF[v];
            sum1 += dpT[v];
        }
        T0[i] = sum0;
        T1[i] = sum1;
    }
    ll ans = 0;
    for (auto &cyc : cycles)
    {
        int k = cyc.size();
        if (k == 1)
        {
            int v = cyc[0];
            ans += T1[v];
            continue;
        }
        vector<int> order;
        int start = cyc[0];
        order.push_back(start);
        int cur = a[start];
        while (cur != start)
        {
            order.push_back(cur);
            cur = a[cur];
        }
        vector<vector<ll>> dp(k, vector<ll>(2, INF));
        dp[0][1] = c[order[0]] + T1[order[0]];
        dp[0][0] = INF;
        for (int i = 1; i < k; i++)
        {
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + c[order[i]] + T1[order[i]];
            dp[i][0] = dp[i - 1][1] + T0[order[i]];
        }
        ll resA = min(dp[k - 1][0], dp[k - 1][1]);
        vector<vector<ll>> dp2(k, vector<ll>(2, INF));
        dp2[0][0] = T0[order[0]];
        dp2[0][1] = INF;
        for (int i = 1; i < k; i++)
        {
            dp2[i][1] = min(dp2[i - 1][0], dp2[i - 1][1]) + c[order[i]] + T1[order[i]];
            dp2[i][0] = dp2[i - 1][1] + T0[order[i]];
        }
        ll resB = dp2[k - 1][1];
        ans += min(resA, resB);
    }
    cout << ans << "\n";
    return 0;
}
