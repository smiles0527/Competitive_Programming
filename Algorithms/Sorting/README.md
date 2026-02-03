# Sorting Algorithms

This directory contains standalone C++ implementations of common sorting algorithms.

## Implementations

| Algorithm        | File                             | Complexity                    | Notes                          |
|------------------|----------------------------------|-------------------------------|--------------------------------|
| Insertion Sort   | insertion_sort/insertion_sort.cpp | O(n²) avg, O(n) best         | Stable; great for small arrays |
| Selection Sort   | selection_sort/selection_sort.cpp | O(n²) all cases              | Few swaps; not stable          |
| Quick Sort       | quick_sort/quick_sort.cpp         | O(n log n) avg, O(n²) worst  | Fast in practice; not stable   |
| Heap Sort        | heap_sort/heap_sort.cpp           | O(n log n) all cases         | Predictable; in-place          |
| Merge Sort       | merge_sort/merge_sort.cpp         | O(n log n) all cases         | Stable; O(n) space             |

## Compile (example)

```
g++ insertion_sort/insertion_sort.cpp -o insertion_sort
```
