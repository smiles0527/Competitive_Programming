#include <bits/stdc++.h>
using namespace std;
 

int N, Q;
vector<int> fArr; 
vector<int> seg;  
 

void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx] = fArr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);
    seg[idx] = max(seg[idx*2], seg[idx*2+1]);
}
 

void updateSeg(int idx, int l, int r, int pos, int val) {
    if(l == r) {
        seg[idx] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid)
        updateSeg(idx*2, l, mid, pos, val);
    else
        updateSeg(idx*2+1, mid+1, r, pos, val);
    seg[idx] = max(seg[idx*2], seg[idx*2+1]);
}
 

int findLeftmost(int idx, int l, int r, int target) {
    if(l == r) return l;
    int mid = (l + r) / 2;
    if(seg[idx*2] == target)
        return findLeftmost(idx*2, l, mid, target);
    else
        return findLeftmost(idx*2+1, mid+1, r, target);
}
 

int findRightmost(int idx, int l, int r, int target) {
    if(l == r) return l;
    int mid = (l + r) / 2;
    if(seg[idx*2+1] == target)
        return findRightmost(idx*2+1, mid+1, r, target);
    else
        return findRightmost(idx*2, l, mid, target);
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N >> Q;
    
    vector<int> cowVote(N+1);
    fArr.resize(N+1, 0);
    for (int i = 1; i <= N; i++){
        cin >> cowVote[i];
        fArr[cowVote[i]]++;
    }
    
    
    set<int> nonzero;
    for (int i = 1; i <= N; i++){
        if(fArr[i] > 0) nonzero.insert(i);
    }
    
    
    seg.resize(4*(N+1), 0);
    build(1, 1, N);
    
    
    auto getAnswer = [&]() -> int {
        if(nonzero.size() < 2) return 0;
        int L = *nonzero.begin();
        int R = *nonzero.rbegin();
        int freqL = fArr[L], freqR = fArr[R];
        int M = seg[1]; 
        
        if(freqL + freqR >= M) return R - L;
        
        int leftM = findLeftmost(1, 1, N, M);
        int rightM = findRightmost(1, 1, N, M);
        return max(R - leftM, rightM - L);
    };
    
    
    
    for (int qi = 0; qi < Q; qi++){
        int i, x;
        cin >> i >> x;
        int oldVote = cowVote[i];
        if(oldVote == x){
            cout << getAnswer() << "\n";
            continue;
        }
        cowVote[i] = x;
        
        
        int oldVal = fArr[oldVote];
        fArr[oldVote]--;
        int newValOld = fArr[oldVote];
        updateSeg(1, 1, N, oldVote, newValOld);
        if(oldVal > 0 && newValOld == 0)
            nonzero.erase(oldVote);
 
        
        int oldVal2 = fArr[x];
        fArr[x]++;
        int newValX = fArr[x];
        updateSeg(1, 1, N, x, newValX);
        if(oldVal2 == 0 && newValX > 0)
            nonzero.insert(x);
 
        cout << getAnswer() << "\n";
    }
    
    return 0;
}
