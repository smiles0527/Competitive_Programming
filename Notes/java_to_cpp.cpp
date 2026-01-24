// ============================================================================
// JAVA TO C++ TRANSITION GUIDE
// ============================================================================
// This file demonstrates key differences and equivalences between Java and C++
// For competitive programming, C++ is preferred due to speed and efficiency
// ============================================================================

#include <bits/stdc++.h>  // Covers nearly all standard headers (import java.* equivalent)
// Alternatively, include manually:
#include <iostream>       // Input/output (System.out, Scanner equivalent)
#include <string>         // String handling
#include <vector>         // Dynamic arrays (ArrayList equivalent)
#include <map>            // Hash maps (HashMap equivalent)
#include <set>            // Sets (HashSet equivalent)
#include <queue>          // Queues (Queue equivalent)
#include <stack>          // Stacks (Stack equivalent)
#include <algorithm>      // Sorting, searching, manipulation
#include <cmath>          // Math functions
#include <cstdio>         // printf, scanf
#include <cstring>        // String operations (memset, memcpy)
#include <cctype>         // Character checks (isalpha, isdigit)
#include <cassert>        // Assertions
#include <cfloat>         // Float limits

using namespace std;  // Avoid std:: prefix everywhere (don't do this in production!)

int main(){
    // ========== I/O: Input and Output ==========
    // Java: System.out.println("Hello"); | C++: cout << "Hello" << endl;
    cout << "Hello World" << endl;  // endl flushes buffer; use "\n" for speed
    
    // Java: Scanner scanner = new Scanner(System.in); int x = scanner.nextInt();
    // C++: Much simpler!
    int x;
    cin >> x;  // Read integer
    cout << x << endl;
    
    // Java: String s = new String("Hello");
    // C++: String is built-in (lowercase)
    string s = "Hello World";
    cout << s << endl;
    
    // Reading strings (note: cin >> stops at whitespace)
    string word;
    cin >> word;  // Reads until space
    
    // For full line input:
    string line;
    getline(cin, line);  // Reads entire line including spaces
    
    // ========== ARRAYS ==========
    // Fixed-size arrays (stack-allocated)
    int arr[10];  // Java: int[] arr = new int[10];
    arr[0] = 1;
    arr[1] = 2;
    cout << arr[0] << endl;
    
    // Multi-dimensional arrays
    int matrix[3][3];  // Java: int[][] matrix = new int[3][3];
    matrix[0][0] = 5;
    cout << matrix[0][0] << endl;
    
    // IMPORTANT: Fixed arrays don't store size! You must track it manually
    // For this reason, competitive programming uses VECTORS instead
    
    // ========== VECTORS (Dynamic Arrays) ==========
    // Java: ArrayList<Integer> v = new ArrayList<Integer>();
    // C++: vector<int> v;
    
    vector<int> v;
    v.push_back(1);    // Java: v.add(1);
    v.push_back(2);
    v.push_back(3);
    
    cout << v[0] << endl;      // Access by index: v[0]
    cout << v.at(0) << endl;   // Safer access with bounds checking
    cout << v.size() << endl;  // Java: v.size()
    
    // Initialize vectors with size
    vector<int> v2(10);           // Size 10, all zeros
    vector<int> v3(10, 5);        // Size 10, all values 5
    vector<int> v4 = {1, 2, 3};   // Initialize with values
    
    // Vector methods
    v.pop_back();           // Java: v.remove(v.size()-1);
    v.clear();              // Clear all elements
    v.empty();              // Check if empty
    
    // Insert at position
    v.insert(v.begin() + 1, 99);  // Insert 99 at index 1
    
    // Erase at position
    v.erase(v.begin() + 1);  // Remove element at index 1
    
    // Multi-dimensional vectors
    vector<vector<int>> matrix2;  // Java: ArrayList<ArrayList<Integer>>
    vector<int> row = {1, 2, 3};
    matrix2.push_back(row);
    cout << matrix2[0][0] << endl;
    
    // ========== MAPS (Hash Maps / Dictionaries) ==========
    // Java: HashMap<String, Integer> map = new HashMap<>();
    // C++: map<string, int> map;
    
    map<string, int> map;
    map["apple"] = 5;       // Java: map.put("apple", 5);
    map["banana"] = 3;
    
    cout << map["apple"] << endl;      // Access value: map["apple"]
    cout << map.size() << endl;        // Number of pairs
    
    // Check if key exists
    if (map.count("apple")) {          // Java: if (map.containsKey("apple"))
        cout << "Found apple" << endl;
    }
    
    // Iterate through map
    for (auto& p : map) {
        cout << p.first << " -> " << p.second << endl;  // key -> value
    }
    
    // ========== SETS (Hash Sets) ==========
    // Java: HashSet<Integer> set = new HashSet<>();
    // C++: set<int> set;  (stores sorted) OR unordered_set<int> set;
    
    set<int> myset;
    myset.insert(5);        // Java: set.add(5);
    myset.insert(3);
    myset.insert(7);
    
    cout << myset.size() << endl;      // Number of elements
    
    if (myset.count(5)) {              // Java: if (set.contains(5))
        cout << "Found 5" << endl;
    }
    
    myset.erase(5);         // Java: set.remove(5);
    
    // ========== STACKS ==========
    // Java: Stack<Integer> stack = new Stack<>();
    // C++: stack<int> stack;
    
    stack<int> mystack;
    mystack.push(1);        // Add to top: stack.push(1);
    mystack.push(2);
    mystack.push(3);
    
    cout << mystack.top() << endl;     // Peek: stack.peek(); (returns 3)
    mystack.pop();                     // Remove from top
    cout << mystack.size() << endl;
    
    // ========== QUEUES ==========
    // Java: Queue<Integer> queue = new LinkedList<>();
    // C++: queue<int> queue;
    
    queue<int> myqueue;
    myqueue.push(1);        // Add to back
    myqueue.push(2);
    myqueue.push(3);
    
    cout << myqueue.front() << endl;   // First element
    myqueue.pop();                     // Remove from front
    cout << myqueue.size() << endl;
    
    // ========== SORTING ==========
    // Java: Collections.sort(list); Arrays.sort(array);
    // C++: sort(v.begin(), v.end());
    
    vector<int> tosort = {5, 2, 8, 1, 9};
    sort(tosort.begin(), tosort.end());     // Ascending
    // Result: [1, 2, 5, 8, 9]
    
    sort(tosort.begin(), tosort.end(), greater<int>());  // Descending
    // Result: [9, 8, 5, 2, 1]
    
    // Custom comparator (sort pairs by second element)
    vector<pair<int,int>> pairs = {{1,3}, {4,1}, {2,2}};
    sort(pairs.begin(), pairs.end(), [](pair<int,int> a, pair<int,int> b) {
        return a.second < b.second;  // Lambda function (Java: (a, b) -> a.getSecond() < b.getSecond())
    });
    
    // ========== COMMON ALGORITHMS ==========
    vector<int> nums = {1, 2, 3, 4, 5};
    
    // Find
    auto it = find(nums.begin(), nums.end(), 3);  // Java: nums.contains(3)
    if (it != nums.end()) {
        cout << "Found 3" << endl;
    }
    
    // Min/Max
    int minval = *min_element(nums.begin(), nums.end());  // Java: Collections.min(nums)
    int maxval = *max_element(nums.begin(), nums.end());  // Java: Collections.max(nums)
    cout << "Min: " << minval << ", Max: " << maxval << endl;
    
    // Reverse
    reverse(nums.begin(), nums.end());  // Java: Collections.reverse(nums)
    
    // Sum (need to implement or use reduce-like approach)
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    // Or use accumulate from <numeric>
    sum = accumulate(nums.begin(), nums.end(), 0);
    
    // ========== LOOPS ==========
    // Traditional for loop (same as Java)
    for (int i = 0; i < 5; i++) {
        cout << i << endl;
    }
    
    // Range-based for loop (Java: for (int x : array))
    vector<int> arr2 = {10, 20, 30};
    for (int val : arr2) {
        cout << val << endl;
    }
    
    // While loop (same as Java)
    int count = 0;
    while (count < 5) {
        cout << count << endl;
        count++;
    }
    
    // ========== KEY DIFFERENCES SUMMARY ==========
    /*
    MEMORY MANAGEMENT:
    - Java: Automatic garbage collection
    - C++: Manual or smart pointers (in modern C++)
    
    SPEED:
    - C++ is significantly faster (no VM overhead)
    - Why competitive programmers use C++
    
    SYNTAX:
    - Java verbose, C++ concise
    - Java: ArrayList<Integer>, C++: vector<int>
    - Java: System.out.println(), C++: cout <<
    
    LIBRARIES:
    - Java: More frameworks (Spring, etc.)
    - C++: STL for competitive programming
    
    COMPETITIVE PROGRAMMING ADVANTAGES OF C++:
    1. Direct memory access (pointers, references)
    2. Fast I/O with cin/cout
    3. STL with optimized algorithms
    4. No garbage collection overhead
    5. Competitive time limits favor C++
    */
    
    return 0;