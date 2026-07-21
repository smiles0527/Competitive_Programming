# Counting Rooms

## Problem

- **Source:** [CSES 1192: Counting Rooms](https://cses.fi/problemset/task/1192/)
- **Code:** [`View accepted C++ solution (countingrooms.cpp)`](./countingrooms.cpp)
- **Constraints:** $1\le n,m\le1000$.

Compute the number of connected regions of floor cells in a grid, where movement is allowed between horizontally or vertically adjacent floor cells.

## Idea

Model each floor cell as a vertex. Connect two vertices if their cells are side-adjacent. A room is then a connected component of this undirected grid graph.

Scan all cells. Once an unvisited floor cell is encountered, it cannot belong to any previously discovered component. Running a flood fill from it traverses every cell in this component without visiting a wall or a different component. Hence one counter increment represents one room.

The grid may contain up to $10^6$ cells. A recursive DFS could create a call chain of this length in a corridor-shaped room, so the implementation uses an explicit vector stack.

## Algorithm

Scan all cells in row-major order. Whenever an unvisited floor cell is found, increment the room counter and run iterative DFS from it. Mark every valid four-neighbor cell before pushing it onto the stack.

## Correctness

Each DFS follows only side-adjacency edges between floor cells, so every cell it marks belongs to the room containing its start cell. Conversely, any cell in the same room is reachable through a sequence of floor cells. Induction along this path shows that the search eventually visits that cell as well.

Once a component has been completed, no later scan position inside it can start another DFS. Every room has a first cell in row-major order, and that cell starts exactly one traversal. Therefore rooms and started traversals correspond one-to-one, so the counter is correct.

## Implementation

Cells are marked when pushed rather than when popped, preventing duplicate stack entries. The global `vis` array satisfies the official $1000\times1000$ constraint. The function keeps the name `dfs` even though it uses an explicit stack.

## Complexity

Each cell is marked and processed at most once, with four neighbor checks. The time complexity is $O(nm)$ and the auxiliary space complexity is $O(nm)$ in the worst case.

## Worked Example

If two open areas touch only diagonally, a search starting in one area cannot cross into the other because only four directional moves are generated. The scan therefore starts two flood fills and counts two rooms.
