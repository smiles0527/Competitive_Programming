// TLE TO BE FIXED
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static const ull INF = (ull)4e18;

struct N {
    char c;
    ull len;
    vector<int> k;
    vector<ull> p;
};

vector<N> g;
int rt[26];

ull addcap(ull a, ull b){ ull c=a+b; return c>=INF||c<a?INF:c; }

int mkleaf(char c){
    g.push_back({c,1,{},{}});
    return (int)g.size()-1;
}

int mkcat(const string& s){
    vector<int> k; k.reserve(s.size());
    for(char ch: s) k.push_back(rt[ch-'a']);
    vector<ull> p; p.reserve(k.size());
    ull cur=0;
    for(int id: k){ cur=addcap(cur,g[id].len); p.push_back(cur); }
    g.push_back({0,cur,move(k),move(p)});
    return (int)g.size()-1;
}

void emit(int id, ull l, ull r, string& out){
    if(l>=r) return;
    if(g[id].len<=l) return;
    if(r>g[id].len) r=g[id].len;
    if(g[id].k.empty()){
        if(l==0 && r==1) out.push_back(g[id].c);
        return;
    }
    auto &k=g[id].k; auto &p=g[id].p;
    int i = (int)(upper_bound(p.begin(), p.end(), l) - p.begin());
    for(; i<(int)k.size(); i++){
        ull st = i? p[i-1]:0, en=p[i];
        if(st>=r) break;
        ull nl = l>st? l-st:0, nr = r<en? r-st:en-st;
        emit(k[i], nl, nr, out);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull a,b; int m;
    cin>>a>>b>>m;
    vector<char> c(m);
    vector<string> s(m);
    for(int i=0;i<m;i++) cin>>c[i]>>s[i];

    g.reserve(26 + 2*m + 5);
    for(int i=0;i<26;i++) rt[i]=mkleaf('a'+i);

    for(int i=m-1;i>=0;i--) rt[c[i]-'a']=mkcat(s[i]);

    string out; out.reserve((size_t)(b-a+1));
    emit(rt[0], a-1, b, out);
    cout<<out<<"\n";
    return 0;
}
