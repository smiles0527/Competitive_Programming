# Competitive Programming Solutions

A comprehensive collection of solutions to competitive programming problems from top-tier programming contests. This repository includes solutions in **C++** from contests such as IOI, USACO, CCC, CodeForces, and more, along with detailed algorithm explanations and data structure implementations.

## About

The solutions are organized by contest and difficulty level, with implementations of common algorithms and data structures essential for competitive programming success. Each solution is written in C++17 using modern competitive programming practices and conventions.

## Documentation

Comprehensive guides organized by topic for systematic learning:

| Document | Description |
|----------|-------------|
| [Notes/basics.md](Notes/basics.md) | Core C++/STL, I/O, complexity analysis |
| [Notes/strategies.md](Notes/strategies.md) | Problem-solving patterns and heuristics |
| [Notes/data_structures.md](Notes/data_structures.md) | Arrays, stacks, trees, heaps, hash tables |
| [Notes/sorting.md](Notes/sorting.md) | Sorting algorithms with implementations |
| [Notes/searching.md](Notes/searching.md) | Search algorithms (binary, linear, etc.) |
| [Notes/mathematics.md](Notes/mathematics.md) | Number theory, combinatorics, modular arithmetic |
| [Notes/greedy.md](Notes/greedy.md) | Greedy algorithm strategies |
| [Notes/graphs.md](Notes/graphs.md) | Graph algorithms and traversal techniques |
| [Notes/dp.md](Notes/dp.md) | Dynamic programming patterns |
| [Notes/backtracking.md](Notes/backtracking.md) | Backtracking and constraint satisfaction |
| [Notes/linear_algebra.md](Notes/linear_algebra.md) | Matrices, transformations, grid problems |
| [CP Template](Algorithms/template.cpp) | Production-ready competitive programming template |

## Contest Solutions

| Contest | Level | Solutions |
|---------|-------|-----------|
| USACO | Bronze → Platinum | [Solutions](USACO/) |
| CCC | Junior → Senior | [Solutions](CCC/) |
| CodeForces | Div. 1-3 | [Solutions](CodeForces/) |
| IOI | International | [Solutions](IOI/) |
| CSES | Introductory | [Solutions](CSES%20question%20set/) |
| CCO | Canadian Computing | [Solutions](CCO/) |
| Other Competitions | Various | [Solutions](Trivial%20Competitions/) |

## Repository Structure

```
Competitive_Programming-1/
├── Algorithms/                    # Core algorithms library
│   ├── template.cpp              # Main CP template with utilities
│   ├── Sorting/                  # Sorting algorithms
│   │   ├── bubble_sort/         # Bubble sort implementation
│   │   ├── insertion_sort/      # Insertion sort implementation
│   │   ├── merge_sort/          # Merge sort implementation
│   │   ├── quick_sort/          # Quick sort implementation
│   │   └── selection_sort/      # Selection sort implementation
│   ├── searching/                # Search algorithms
│   │   ├── binary_search/       # Binary search implementation
│   │   ├── exponential_search/  # Exponential search implementation
│   │   ├── interpolation_search/# Interpolation search implementation
│   │   ├── jump_search/         # Jump search implementation
│   │   └── linear_search/       # Linear search implementation
│   ├── backtracking/             # Backtracking algorithms
│   │   ├── all_permutations/    # Generate all permutations
│   │   ├── all_combinations/    # Generate all combinations
│   │   ├── string_pattern/      # String pattern matching
│   │   ├── generating_words/    # Word generation from grids
│   │   ├── hamiltonian_paths/   # Hamiltonian path finding
│   │   ├── k_colorable_configurations/ # Graph coloring
│   │   ├── knight_tour/         # Knight's tour problem
│   │   ├── topological_sort/    # Topological ordering
│   │   └── minimax/             # Minimax algorithm (tic-tac-toe)
│   ├── strategies/               # Problem-solving strategies
│   │   ├── lru_cache/           # LRU cache implementation
│   │   ├── k_closest_points/    # K closest points problem
│   │   ├── subarray_sum/        # Subarray sum problems
│   │   └── ... (15 total)
│   ├── collections_containers/   # Data structures
│   │   ├── avl_tree/            # AVL tree implementation
│   │   ├── binary_search_tree/  # BST implementation
│   │   ├── hash_table/          # Hash table implementation
│   │   └── ... (9 total)
│   ├── graph_theory/            # Graph algorithms (BFS, DFS, Dijkstra)
│   ├── DP/                      # Dynamic programming problems
│   └── resources/               # Diagrams and references
├── Notes/                        # Comprehensive documentation
│   ├── basics.md                # C++/STL fundamentals
│   ├── strategies.md            # Problem-solving guide
│   ├── data_structures.md       # Data structures reference
│   ├── sorting.md               # Sorting algorithms
│   ├── searching.md             # Searching algorithms
│   ├── mathematics.md           # Math for CP
│   ├── greedy.md                # Greedy algorithms
│   ├── graphs.md                # Graph theory
│   ├── dp.md                    # Dynamic programming
│   ├── backtracking.md          # Backtracking guide
│   └── linear_algebra.md        # Matrices and grids
├── USACO/                        # USACO problems by year/level
├── CCC/                          # Canadian Computing Contest
├── CodeForces/                   # CodeForces submissions
├── CSES question set/            # CSES problem solutions
├── IOI/                          # International Olympiad
├── CCO/                          # Canadian Computing Olympiad
├── Trivial Competitions/         # Other contest platforms
├── LeetCode questions/           # LeetCode solutions
└── z_misc questions/             # Miscellaneous practice
```

## Algorithm Implementations

All algorithm implementations follow a consistent structure:
- **Single file format**: Each algorithm is consolidated into a standalone `.cpp` file
- **C++17 standard**: Uses modern C++17 features (`std::optional`, `std::nullopt`, etc.)
- **bits/stdc++.h**: Competitive programming header for convenience
- **Clean implementations**: No external dependencies beyond standard library

## Key Resources

### Main Template
The [Algorithms/template.cpp](Algorithms/template.cpp) contains a production-ready CP template with:
- Fast I/O optimization
- Common macros and utilities
- Type aliases for competitive programming
- Binary search templates
- Debugging macros

### Algorithm Library
Each algorithm category includes:
- **Sorting** (5 algorithms): Bubble, insertion, merge, quick, selection sort
- **Searching** (5 algorithms): Binary, exponential, interpolation, jump, linear search
- **Backtracking** (9 problems): Permutations, combinations, N-Queens, knight tour, graph coloring
- **Strategies** (15 patterns): LRU cache, sliding window, two-pointer, backtracking patterns
- **Data Structures** (9 implementations): Trees, heaps, hash tables, linked lists

All implementations include comprehensive documentation in the Notes/ directory with links to source code.

## Getting Started

1. **Learn the basics**: Start with [Notes/basics.md](Notes/basics.md)
2. **Study algorithms**: Follow the reading order in documentation
3. **Practice**: Solve problems from USACO, CCC, or CodeForces
4. **Use the template**: Copy [Algorithms/template.cpp](Algorithms/template.cpp) for contests

## Build Information

- **Language**: C++17
- **Compiler**: g++ (MinGW-w64) with `-std=c++17` flag
- **Platform**: Windows with MSYS2/MinGW-w64
- **Headers**: Uses `bits/stdc++.h` for competitive programming convenience


