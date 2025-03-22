#include <bits/stdc++.h>
using namespace std;

struct CandidateSegTree {
    int n, size;
    vector<int> tree;
    CandidateSegTree(int n) : n(n) {
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2 * size, -1);
    }
    void build(vector<int>& arr) {
        for (int i = 0; i < n; i++)
            tree[size + i] = arr[i];
        for (int i = n; i < size; i++)
            tree[size + i] = -1;
        for (int i = size - 1; i >= 1; i--)
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
    void update(int idx, int val) {
        int i = size + idx;
        tree[i] = val;
        i /= 2;
        while(i) {
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
            i /= 2;
        }
    }
    
    int query_leftmost(int threshold) {
        if(tree[1] < threshold)
            return -1;
        int i = 1;
        while(i < size) {
            if(tree[2 * i] >= threshold)
                i = 2 * i;
            else
                i = 2 * i + 1;
        }
        return i - size;
    }
    
    int query_rightmost(int threshold) {
        if(tree[1] < threshold)
            return -1;
        int i = 1;
        while(i < size) {
            if(tree[2 * i + 1] >= threshold)
                i = 2 * i + 1;
            else
                i = 2 * i;
        }
        return i - size;
    }
};
 


struct FreqSegTree {
    int m, size;
    vector<int> tree;
    FreqSegTree(int m) : m(m) {
        size = 1;
        while(size < m) size *= 2;
        tree.assign(2 * size, 0);
    }
    void build(vector<int>& arr) {
        for (int i = 0; i < m; i++)
            tree[size + i] = arr[i];
        for (int i = m; i < size; i++)
            tree[size + i] = 0;
        for (int i = size - 1; i >= 1; i--)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
    
    void update(int pos, int delta) {
        int i = size + pos;
        tree[i] += delta;
        i /= 2;
        while(i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
            i /= 2;
        }
    }
    
    void set_val(int pos, int val) {
        int i = size + pos;
        tree[i] = val;
        i /= 2;
        while(i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
            i /= 2;
        }
    }
    
    int query_count(int pos) {
        return tree[size + pos];
    }
    
    int query_global_max() {
        int idx = 1;
        if(tree[1] == 0) return 0;
        while(idx < size) {
            int rightChild = 2 * idx + 1;
            int leftChild = 2 * idx;
            if(tree[rightChild] > 0)
                idx = rightChild;
            else
                idx = leftChild;
        }
        return idx - size;
    }
    
    
    
    int query_second_max(int global_max) {
        if(query_count(global_max) >= 2)
            return global_max;
        int orig = tree[size + global_max];
        set_val(global_max, 0);
        int second_max = query_global_max();
        set_val(global_max, orig);
        return second_max;
    }
};
 

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N);
    
    vector<int> f(N + 1, 0);
    for (int i = 0; i < N; i++){
        cin >> a[i];
        f[a[i]]++;
    }
    
    vector<int> candArr(N, -1);
    for (int c = 1; c <= N; c++){
        if(f[c] > 0)
            candArr[c - 1] = f[c];
    }
    CandidateSegTree candSeg(N);
    candSeg.build(candArr);
 
    
    int maxFreqPossible = N + 1;
    vector<int> countFreq(maxFreqPossible, 0);
    for (int c = 1; c <= N; c++){
        countFreq[f[c]]++;
    }
    FreqSegTree freqSeg(maxFreqPossible);
    freqSeg.build(countFreq);
 
    
    set<int> S;
    for (int c = 1; c <= N; c++){
        if(f[c] > 0)
            S.insert(c);
    }
 
    auto query_rightmost_candidate = [&](int th) -> int {
        th = max(th, 0);
        return candSeg.query_rightmost(th);
    };
    auto query_leftmost_candidate = [&](int th) -> int {
        th = max(th, 0);
        return candSeg.query_leftmost(th);
    };
 
    vector<string> out;
    for (int qi = 0; qi < Q; qi++){
        int i, x;
        cin >> i >> x;
        int old = a[i - 1];
        if(old != x){
            a[i - 1] = x;
            
            int prev = f[old];
            f[old]--;
            int newVal = f[old];
            if(newVal == 0){
                candSeg.update(old - 1, -1);
                S.erase(old);
            } else {
                candSeg.update(old - 1, newVal);
            }
            freqSeg.update(prev, -1);
            freqSeg.update(newVal, 1);
 
            
            prev = f[x];
            f[x]++;
            newVal = f[x];
            if(prev == 0){
                candSeg.update(x - 1, newVal);
                S.insert(x);
            } else {
                candSeg.update(x - 1, newVal);
            }
            freqSeg.update(prev, -1);
            freqSeg.update(newVal, 1);
        }
 
        if(S.size() < 2){
            out.push_back("0");
            continue;
        }
        int global_min = *S.begin();
        int global_max = *S.rbegin();
 
        int globalFreq = freqSeg.query_global_max();
        int secondFreq = freqSeg.query_second_max(globalFreq);
 
        
        int optA = 0, optB = 0;
        if(f[global_min] == globalFreq)
            optA = global_max - global_min;
        else {
            int T = globalFreq - f[global_min];
            int cand = query_rightmost_candidate(T);
            if(cand == -1)
                optA = 0;
            else
                optA = (cand + 1) - global_min; 
        }
        if(f[global_max] == globalFreq)
            optB = global_max - global_min;
        else {
            int T = globalFreq - f[global_max];
            int cand = query_leftmost_candidate(T);
            if(cand == -1)
                optB = 0;
            else
                optB = global_max - (cand + 1);
        }
        int best = max(optA, optB);
        out.push_back(to_string(best));
    }
    for(auto &s : out)
        cout << s << "\n";
    return 0;
}
