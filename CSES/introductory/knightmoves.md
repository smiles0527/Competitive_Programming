# Knight Moves Grid

## Problem

- **Source:** [CSES 3217: Knight Moves Grid](https://cses.fi/problemset/task/3217/)
- **Code:** [`View accepted C++ solution (knightmoves.cpp)`](./knightmoves.cpp)
- **Limits:** $4\le n\le1000$.

For every square of an $n\times n$ board, print its minimum knight-move distance to the upper-left square.

## Construction

Represent each board square by a vertex in a graph. Connect two vertices if a knight can move from one corresponding square to the other. Every edge has cost $1$, and every knight move is reversible. A breadth-first search starting from the corner $(0,0)$ therefore finds the distance from the corner to every square, which is exactly what we need.

### Procedure

Initially set every distance to $-1$, which represents infinity. Set $\texttt{dist}[0][0]=0$ and insert the corner into the queue. While the queue is not empty, remove its next square and inspect all eight possible knight destinations. For every valid unvisited neighbor, set its distance to the current distance plus one and insert it into the queue. Finally, output the distance matrix.

## Why it works

Breadth-first search processes vertices in nondecreasing order of their distance from the source. When an unvisited square is first reached from a square at distance $d$, we have found a path of length $d+1$ to it. If a shorter path existed, that path would reach the square from an earlier BFS layer, so the square would already have been visited. Therefore, every stored value is the shortest distance from the corner. Since knight moves are reversible, it is also the shortest distance back to the corner.

## Implementation

The arrays `dr` and `dc` enumerate the eight possible knight moves. The value $-1$ serves both as infinity and as the test for whether a square has been visited.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;

	vector<vector<int>> dist(n, vector<int>(n, -1));
	queue<pair<int, int>> q;

	dist[0][0] = 0;
	q.push({0, 0});

	int dr[8] = {2, 2, -2, -2, 1, 1, -1, -1};
	int dc[8] = {1, -1, 1, -1, 2, -2, 2, -2};

	while(!q.empty()){
		auto [r, c] = q.front();
		q.pop();
		for(int i = 0; i < 8; i++){
			int nr = r + dr[i], nc = c + dc[i];
			if(0 <= nr && nr < n && 0 <= nc && nc < n && dist[nr][nc] == -1){
				dist[nr][nc] = dist[r][c]+1;
				q.push({nr, nc});
			}
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
		cout << dist[i][j] << (j + 1 == n ? '\n' : ' ');
		}
	}
	return 0;
}
```

## Complexity

The graph has $n^2$ vertices and at most eight outgoing edges per vertex. Time and space are $O(n^2)$.

## Example

From $(0,0)$, the first BFS layer contains $(1,2)$ and $(2,1)$. Squares reached from those nodes but not earlier receive distance two.
