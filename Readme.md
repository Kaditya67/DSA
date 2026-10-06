# 🧩 DSA Mastery — Pattern Sheet Roadmap

A structured reference guide covering **17 Data Structures & Algorithms modules**, organized into distinct problem-solving patterns with intuition cues, trigger signals, and problem counts.

---

## 📊 Modules & Pattern Overview

| # | Topic | Sub-Patterns | Total Problems |
|:---:|:---|:---:|:---:|
| 1 | [Array](#1-array) | 4 | 24 |
| 2 | [Strings](#2-strings) | 2 | 11 |
| 3 | [Binary Search](#3-binary-search) | 4 | 23 |
| 4 | [Stack](#4-stack) | 7 | 32 |
| 5 | [Queue](#5-queue) | 2 | 6 |
| 6 | [Recursion](#6-recursion) | 5 | 20 |
| 7 | [Linked List](#7-linked-list) | 5 | 29 |
| 8 | [Doubly Linked List](#8-doubly-linked-list) | 2 | 9 |
| 9 | [HashMap](#9-hashmap) | 2 | 5 |
| 10 | [Binary Tree & BST](#10-binary-tree--bst) | 5 | 54 |
| 11 | [Graph](#11-graph) | 7 | 44 |
| 12 | [Heap / Priority Queue](#12-heap--priority-queue) | 4 | 15 |
| 13 | [Backtracking](#13-backtracking) | 4 | 24 |
| 14 | [Greedy](#14-greedy) | 2 | 18 |
| 15 | [Dynamic Programming](#15-dynamic-programming) | 7 | 44 |
| 16 | [Trie](#16-trie) | 3 | 11 |
| 17 | [Bit Manipulation](#17-bit-manipulation) | 3 | 16 |
| **Total** | **All Modules** | **68 Patterns** | **385 Problems** |

---

## 📁 Repository Organization

```text
DSA/
├── Readme.md                          # Global curriculum & pattern index
├── 01-array/
│   ├── two-pointer/                   # Notes & problem solutions
│   ├── sliding-window/
│   ├── prefix-sum/
│   └── kadanes-algorithm/
├── 02-strings/
│   ├── two-pointer-palindrome/
│   └── sliding-window-string/
├── 03-binary-search/
│   ├── classic-binary-search/
│   ├── lower-upper-bound/
│   ├── binary-search-on-answers/
│   └── search-in-2d-matrix/
├── 04-stack/
├── 05-queue/
├── 06-recursion/
├── 07-linked-list/
├── 08-doubly-linked-list/
├── 09-hashmap/
├── 10-binary-tree/
├── 11-graph/
├── 12-heap/
├── 13-backtracking/
├── 14-greedy/
├── 15-dynamic-programming/
├── 16-trie/
├── 17-bit-manipulation/
└── templates/                         # Pattern boilerplates & reusable templates
```

---

## 1. Array
> *Fundamental collection of elements stored at contiguous memory locations.* (24 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Two-Pointer** | Pairs, sorted arrays, triplets, opposite-end or fast-slow traversal | 6 |
| **Sliding Window** | Subarray of size $k$, longest/shortest contiguous subarray, at most $K$ | 8 |
| **Prefix Sum** | Range sum queries, subarray sum equals $K$, cumulative sums | 6 |
| **Kadane’s Algorithm** | Maximum/minimum contiguous subarray sum or product | 4 |

---

## 2. Strings
> *Sequence of characters and common string manipulation patterns.* (11 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Two-Pointer (Palindrome)** | Palindrome verification, symmetric comparisons, reverse from both ends | 5 |
| **Sliding Window (String)** | Longest/shortest substring without repeat, at most $K$ distinct characters | 6 |

---

## 3. Binary Search
> *Efficient logarithmic search algorithm dividing the search interval in half.* (23 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Classic Binary Search** | Sorted array, finding target element in $O(\log N)$ | 6 |
| **Lower / Upper Bound** | First/last occurrence, floor/ceil, index boundary constraints | 5 |
| **Binary Search on Answers** | Minimum/maximum feasible value, allocation problems, monotonic predicate | 8 |
| **Search in 2D Matrix** | Row-wise & column-wise sorted matrix, $k$-th smallest element in matrix | 4 |

---

## 4. Stack
> *LIFO (Last In First Out) data structure patterns.* (32 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Monotonic Stack** | Next/previous greater/smaller element, stock span, largest rectangle in histogram | 7 |
| **Expression Evaluation** | Infix/postfix/prefix evaluation, decode strings, basic calculator | 4 |
| **Stack Simulation / Undo** | Backspace compare, remove adjacent duplicates, simulation | 4 |
| **Parenthesis & Scoring** | Valid parentheses, minimum additions to balance, score of parentheses | 4 |
| **Stack-Based Design** | Min Stack, Max Stack, implement Queue using Stacks | 5 |
| **Stack + Greedy** | Remove $K$ digits, smallest subsequence of distinct characters | 5 |
| **Recursive Stack** | Reverse stack using recursion, sort stack recursively | 3 |

---

## 5. Queue
> *FIFO (First In First Out) sequential processing.* (6 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Queue & Circular Queue** | Implement circular queue/deque, wrap-around buffer management | 3 |
| **Queue Simulation / FIFO** | Arrival order processing, circular potato/Josephus game, task scheduling | 3 |

---

## 6. Recursion
> *Breaking down problems into smaller, self-similar subproblems.* (20 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Linear Recursion** | Single linear branching, base case reduction | 4 |
| **Non-Linear Recursion** | Multiple branch recursion, tree of choices, grid paths | 4 |
| **Divide & Conquer** | Merge sort, quick sort, search in structured sub-halves | 5 |
| **Recursion on LinkedList/Stack** | Reverse list recursively, recursive stack operations | 4 |
| **Subsequences** | Include / exclude choices, generate power set, target sum subsets | 3 |

---

## 7. Linked List
> *Linear data structure with non-contiguous node memory allocation.* (29 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Basic Operations** | Insertion, deletion at head/tail/Nth node, traversal | 6 |
| **Fast & Slow Pointers** | Cycle detection (Floyd's algorithm), middle node, cycle entry | 4 |
| **Reversal Pattern** | Reverse full list, reverse sublist between $[m, n]$, reverse in $K$-groups | 7 |
| **Merge / Sort** | Merge two sorted lists, merge $K$ sorted lists, sort list | 7 |
| **LinkedList with Stack/Map** | Intersection of lists, copy list with random pointer, reverse order arithmetic | 5 |

---

## 8. Doubly Linked List
> *Linked list with bidirectional forward and backward traversal.* (9 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Basic DLL Operations** | Insert/delete in DLL, LRU Cache / LFU Cache design | 6 |
| **Merge / Sort / Reorder** | Multi-level DLL flattening, pair sums in sorted DLL, palindrome check | 3 |

---

## 9. HashMap
> *Key-value pair data structure for average $O(1)$ lookups.* (5 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Frequency Map / Counting** | Top $K$ frequent, majority element, anagram groupings | 4 |
| **Prefix-Sum with Map** | Subarray sum equals $K$, longest subarray with sum divisible by $K$ | 1 |

---

## 10. Binary Tree & BST
> *Hierarchical tree structure with root, subtrees, and binary search invariants.* (54 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **DFS Traversals** | Pre/In/Postorder, max depth, diameter, path sum I/II/III, max path sum | 17 |
| **BFS / Level-Order** | Level order, zigzag, right/left view, level averages | 11 |
| **Lowest Common Ancestor** | LCA in binary tree, distance between nodes | 3 |
| **Serialization / Construction** | Construct from Inorder+Preorder, serialize/deserialize tree, flatten to list | 6 |
| **BST** | Validate BST, insert/delete, $k$-th smallest, range sum BST | 17 |

---

## 11. Graph
> *Nodes and edges modeling connectivity, networks, and dependencies.* (44 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **DFS (Connectivity)** | Number of islands, cycle detection, bipartite graph, articulation points/bridges | 12 |
| **BFS Pattern** | Shortest path in unweighted graph, word ladder, rotten oranges | 6 |
| **Topological Sort** | Course Schedule, task order, dependency DAGs, Kahn's algorithm | 5 |
| **MST / Union-Find** | Kruskal's, Prim's, Redundant Connection, Disjoint Set Union | 8 |
| **Dijkstra (Weighted)** | Shortest path with non-negative edge weights, min effort path | 7 |
| **Bellman-Ford** | Negative weight edges, negative cycle detection | 3 |
| **Floyd-Warshall** | All-pairs shortest paths, transitive closure | 3 |

---

## 12. Heap / Priority Queue
> *Efficient retrieval of extreme elements (min/max).* (15 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Implementation of Heap** | Min/Max Heap from scratch, heapify, Priority Queue design | 3 |
| **Top-K Elements** | $K$-th largest element, find median from data stream | 5 |
| **Merge K Sorted** | Merge $K$ sorted lists, smallest range covering elements from $K$ lists | 3 |
| **Huffman / Minimum Cost** | Connect ropes with minimum cost, reduce array size | 4 |

---

## 13. Backtracking
> *Incremental recursive exploration with state pruning.* (24 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Choice-Based Backtracking** | Permutations, combinations, subsets II | 9 |
| **Constraint-Based Backtracking** | N-Queens, Sudoku solver, generate parentheses | 6 |
| **Grid / Path Backtracking** | Word search in grid, unique paths III, rat in a maze | 5 |
| **Decision Tree / Sequences** | Letter combinations of phone number, expression add operators | 4 |

---

## 14. Greedy
> *Making locally optimal choices to achieve globally optimal solutions.* (18 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Intervals & Reach** | Non-overlapping intervals, merge intervals, jump game I & II | 10 |
| **Sorting / Local Choice** | Gas station, candy distribution, fractional knapsack | 8 |

---

## 15. Dynamic Programming
> *Overlapping subproblems and optimal substructure.* (44 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **1D / Linear DP** | Climbing stairs, frog jump, house robber | 3 |
| **2D / Grid DP** | Unique paths, minimum path sum, maximal square | 8 |
| **DP on Strings** | Longest Common Subsequence (LCS), Edit Distance, Palindromic Substrings | 10 |
| **DP on Intervals / Partition** | Matrix chain multiplication, burst balloons, palindrome partitioning | 6 |
| **DP on Trees / DAGs** | Binary tree max path sum, house robber III, DAG longest path | 3 |
| **Knapsack / Subset Sum** | 0/1 Knapsack, Coin Change (Unbounded), Target Sum, Partition Equal Subset | 8 |
| **DP on Stocks** | Best time to buy & sell stock I, II, III, IV, with cooldown, with fee | 6 |

---

## 16. Trie
> *Prefix tree for efficient string dictionary search and prefix queries.* (11 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Basic Trie Operations** | Implement Trie (Prefix Tree), Add and Search Word | 5 |
| **Word Break / Segmentation** | Word break problem, word search II with Trie | 3 |
| **Bitwise Trie / XOR** | Maximum XOR of two numbers in an array, maximum XOR with element | 3 |

---

## 17. Bit Manipulation
> *Direct binary manipulation for $O(1)$ arithmetic and set representations.* (16 problems)

| Sub-Pattern | Key Signals / Trigger Words | Problems |
|:---|:---|:---:|
| **Basic Bit Operations** | Single number, counting bits, power of two, reverse bits | 9 |
| **Subsets / Bitmask** | Generate subsets via bitmask, TSP with bitmask DP | 3 |
| **Advanced XOR** | Two single numbers, XOR queries in subarray | 4 |

---

## 📝 Problem Log Template

```markdown
### [Problem Name / LeetCode #]
- **Pattern:** <e.g., Two Pointers / Monotonic Stack / Sliding Window>
- **Difficulty:** Easy / Medium / Hard
- **Core Intuition:** (The key insight — why this pattern works here)
- **Time Complexity:** $O(...)$
- **Space Complexity:** $O(...)$
- **Edge Cases:** Single element, duplicates, negatives, empty input.
- **Solution File:** [solution.py](./solutions/problem.py)
```
