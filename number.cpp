#include <bits/stdc++.h>
using namespace std;

long long answer = -1;
bool found = false;

void dfs(int length, long long prefix, int digitSum, int last1, int last2, vector<bool> &used) {
if (found) return;
if (length == 10) { answer = prefix; found = true; return; }
for (int d = 0; d <= 9; ++d) {
if (length == 0 && d == 0) continue;
if (used[d]) continue;
int k = length + 1;
// quick prunes
if (k == 2 && (d % 2)) continue;
if (k == 5 && !(d == 0 || d == 5)) continue;
if (k == 10 && d != 0) continue;
if (k == 4) { int lastTwo = last1 * 10 + d; if (lastTwo % 4) continue; }
if (k == 8) { int lastThree = (last2 * 10 + last1) * 10 + d; if (lastThree % 8) continue; }
if (k == 3) { if (((digitSum + d) % 3) != 0) continue; }
if (k == 6) { if ((d % 2) || ((digitSum + d) % 3)) continue; }
if (k == 9) { if (((digitSum + d) % 9) != 0) continue; }
long long next = prefix * 10 + d;
if (next % k != 0) continue;
used[d] = true;
dfs(k, next, digitSum + d, d, last1, used);
used[d] = false;
if (found) return;
}
}

int main() {
ios::sync_with_stdio(false);
cin.tie(nullptr);
vector<bool> used(10, false);
dfs(0, 0, 0, 0, 0, used);
if (found) cout << answer << "\n"; else cout << "No solution found" << "\n";
return 0;
}