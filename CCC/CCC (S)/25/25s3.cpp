#include <bits/stdc++.h>
using namespace std;
 
const long long INF = 1e18;
 
struct SegTree {
    int n;
    vector<long long> tree;
    SegTree(int n) : n(n) { tree.assign(4 * n, -1); }
    void updateUtil(int idx, int l, int r, int pos, long long val) {
        if (l == r) {
            tree[idx] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            updateUtil(idx * 2, l, mid, pos, val);
        else
            updateUtil(idx * 2 + 1, mid + 1, r, pos, val);
        tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
    }
    void update(int pos, long long val) { updateUtil(1, 1, n, pos, val); }
    long long queryUtil(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return -1;
        if (ql <= l && r <= qr)
            return tree[idx];
        int mid = (l + r) / 2;
        return max(queryUtil(idx * 2, l, mid, ql, qr),
                   queryUtil(idx * 2 + 1, mid + 1, r, ql, qr));
    }
    long long query(int l, int r) { return (l > r ? -1 : queryUtil(1, 1, n, l, r)); }
};
 
struct PairComp {
    bool operator()(const pair<long long, int>& a, const pair<long long, int>& b) const {
        return (a.first == b.first ? a.second < b.second : a.first < b.first);
    }
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<int> penColor(N + 1);
    vector<long long> penPretty(N + 1);
    vector<multiset<pair<long long, int>>> colorSets(M + 1);
    vector<long long> bestVal(M + 1, 0), secondVal(M + 1, -1);
    vector<int> countBest(M + 1, 0);
    vector<long long> cand(M + 1, -1);
 
    for (int i = 1; i <= N; i++){
        int c; long long p;
        cin >> c >> p;
        penColor[i] = c;
        penPretty[i] = p;
        colorSets[c].insert({p, i});
    }
 
    long long baseSum = 0;
    set<pair<long long, int>, PairComp> globalBestSet;
    for (int c = 1; c <= M; c++){
        auto &ms = colorSets[c];
        auto it = ms.end(); it--;
        bestVal[c] = it->first;
        countBest[c] = 1;
        if (ms.size() >= 2) {
            auto it2 = it; it2--;
            if (it2->first == bestVal[c])
                countBest[c] = 2;
            secondVal[c] = it2->first;
        } else {
            secondVal[c] = -1;
        }
        baseSum += bestVal[c];
        globalBestSet.insert({bestVal[c], c});
        if (ms.size() < 2)
            cand[c] = -1;
        else
            cand[c] = (countBest[c] >= 2 ? bestVal[c] : secondVal[c]);
    }
 
    SegTree segTree(M);
    for (int c = 1; c <= M; c++){
        segTree.update(c, cand[c]);
    }
 
    auto updateColorGroupWithBase = [&](int c, long long oldBest) {
        globalBestSet.erase({bestVal[c], c});
        auto &ms = colorSets[c];
        if (ms.empty()){
            bestVal[c] = 0;
            secondVal[c] = -1;
            countBest[c] = 0;
        } else {
            auto it = ms.end(); it--;
            bestVal[c] = it->first;
            countBest[c] = 1;
            if (ms.size() >= 2) {
                auto it2 = it; it2--;
                if (it2->first == bestVal[c])
                    countBest[c] = 2;
                secondVal[c] = it2->first;
            } else {
                secondVal[c] = -1;
            }
        }
        baseSum = baseSum - oldBest + bestVal[c];
        globalBestSet.insert({bestVal[c], c});
        if (colorSets[c].size() < 2)
            cand[c] = -1;
        else
            cand[c] = (countBest[c] >= 2 ? bestVal[c] : secondVal[c]);
        segTree.update(c, cand[c]);
    };
 
    auto computeAnswer = [&]() -> long long {
        auto it = globalBestSet.begin();
        long long g = it->first;
        int gColor = it->second;
        bool unique = true;
        long long h = INF;
        auto it2 = it; it2++;
        if (it2 != globalBestSet.end()){
            if (it2->first == g)
                unique = false;
            else
                h = it2->first;
        }
        long long bestImprovement = 0;
        if (!unique) {
            long long maxCand = segTree.query(1, M);
            bestImprovement = maxCand - g;
        } else {
            long long cand_g = segTree.query(gColor, gColor);
            long long opt1 = cand_g - h;
            long long opt2 = max(segTree.query(1, gColor - 1), segTree.query(gColor + 1, M)) - g;
            bestImprovement = max(opt1, opt2);
        }
        if (bestImprovement < 0)
            bestImprovement = 0;
        return baseSum + bestImprovement;
    };
 
    cout << computeAnswer() << "\n";
    for (int qi = 0; qi < Q; qi++){
        int type;
        cin >> type;
        if (type == 1) {
            int i, newC;
            cin >> i >> newC;
            int oldC = penColor[i];
            if (oldC == newC) {
                cout << computeAnswer() << "\n";
                continue;
            }
            long long p = penPretty[i];
            long long oldBestOld = bestVal[oldC];
            colorSets[oldC].erase(colorSets[oldC].find({p, i}));
            updateColorGroupWithBase(oldC, oldBestOld);
 
            long long oldBestNew = bestVal[newC];
            colorSets[newC].insert({p, i});
            updateColorGroupWithBase(newC, oldBestNew);
 
            penColor[i] = newC;
        } else {
            int i;
            long long newP;
            cin >> i >> newP;
            int c = penColor[i];
            long long oldP = penPretty[i];
            long long oldBestC = bestVal[c];
            colorSets[c].erase(colorSets[c].find({oldP, i}));
            colorSets[c].insert({newP, i});
            updateColorGroupWithBase(c, oldBestC);
            penPretty[i] = newP;
        }
        cout << computeAnswer() << "\n";
    }
    return 0;
}
