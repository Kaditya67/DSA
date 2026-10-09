# Binary Search Patterns: Quick Reference & Cheatsheet

A concise diagnostic cheatsheet for Binary Search patterns. Use this page to identify whether a problem is a classic array lookup, a boundary detection, an optimization over an answer range, or a 2D matrix traversal.

---

## 1. How to Pick Your Pattern

Ask yourself these diagnostic questions:

1. **Is the input array sorted, and you're looking for an element or pivot?**
   - Exact match, rotated sorted array, or minimum in rotated array $\to$ **[01. Classic Binary Search](./01-classic-binary-search/README.md)**
2. **Are there duplicates, and you need first/last occurrence, floor/ceil, or insertion index?**
   - First occurrence, last occurrence, lower/upper bound $\to$ **[02. Lower & Upper Bound](./02-lower-upper-bound/README.md)**
3. **Is the problem asking to minimize a maximum, maximize a minimum, or optimize a capacity/speed?**
   - The array itself doesn't even need to be sorted; the answer range has a monotonic predicate $\to$ **[03. Binary Search on Answers](./03-binary-search-on-answers/README.md)**
4. **Is the data structured as a 2D grid with sorted rows/columns?**
   - Fully sorted matrix $\to$ 1D mapping `mid / n`, `mid % n` in `O(log(M * N))`
   - Row-wise and column-wise sorted $\to$ Staircase search from Top-Right `(0, n - 1)` in `O(M + N)` $\to$ **[04. Search in 2D Matrix](./04-search-in-2d-matrix/README.md)**

---

## 2. Comparison Matrix

| Pattern | Input Signal | When to Use | Time Complexity | Auxiliary Space |
|:---|:---|:---|:---:|:---:|
| **[01. Classic Binary Search](./01-classic-binary-search/README.md)** | Sorted array, rotated sorted, exact target | Search in Rotated Array, Peak Element | `O(log N)` | `O(1)` |
| **[02. Lower & Upper Bound](./02-lower-upper-bound/README.md)** | Sorted with duplicates, boundary / floor / ceil | First & Last Occurrence, Search Insert Position | `O(log N)` | `O(1)` |
| **[03. Binary Search on Answers](./03-binary-search-on-answers/README.md)** | "Min of max", "Max of min", allocation over range | Koko Bananas, Ship Packages, Split Array | `O(N * log(Range))` | `O(1)` |
| **[04. Search in 2D Matrix](./04-search-in-2d-matrix/README.md)** | Row/Col sorted matrix | Search 2D Matrix I & II, K-th Smallest in Matrix | `O(log(MN))` or `O(M+N)` | `O(1)` |

---

## 3. Visual Decision Tree

```text
Problem asks for efficient O(log N) search or optimization:
│
├── Exact element or pivot in 1D array?
│   ├── No duplicates / Rotated sorted?
│   │   └── 01. Classic Binary Search (while low <= high)
│   └── Duplicates / First or last occurrence / Insert index?
│       └── 02. Lower & Upper Bound (record candidate and narrow)
│
├── Minimization or Maximization problem over an answer space?
│   └── 03. Binary Search on Answers
│       ├── Min of Max: [F, F, F, T, T, T] -> record candidate, high = mid - 1
│       └── Max of Min: [T, T, T, F, F, F] -> record candidate, low = mid + 1
│
└── 2D Grid with sorted properties?
    └── 04. Search in 2D Matrix
        ├── Fully sorted: 1D index mapping (mid / n, mid % n)
        └── Row/Col sorted: Staircase search from Top-Right (0, n - 1)
```

---

## 4. Code Blueprints

### Classic Binary Search
```cpp
int low = 0, high = n - 1;
while (low <= high) {
    int mid = low + (high - low) / 2;
    if (nums[mid] == target) return mid;
    (nums[mid] < target) ? low = mid + 1 : high = mid - 1;
}
return -1;
```

### Lower Bound (`nums[i] >= target`)
```cpp
int low = 0, high = n - 1, ans = n;
while (low <= high) {
    int mid = low + (high - low) / 2;
    if (nums[mid] >= target) { ans = mid; high = mid - 1; }
    else { low = mid + 1; }
}
return ans;
```

### Binary Search on Answers (Minimization)
```cpp
int low = min_val, high = max_val, ans = high;
while (low <= high) {
    int mid = low + (high - low) / 2;
    if (isFeasible(mid)) { ans = mid; high = mid - 1; }
    else { low = mid + 1; }
}
return ans;
```

### Staircase 2D Matrix Search
```cpp
int r = 0, c = n - 1;
while (r < m && c >= 0) {
    if (matrix[r][c] == target) return true;
    (matrix[r][c] > target) ? c-- : r++;
}
return false;
```

---

## 5. Quick Traps Checklist

- [ ] **Did you avoid `(low + high) / 2`?** Always write `low + (high - low) / 2` to prevent 32-bit integer overflow.
- [ ] **Are accumulators `long long` in BS on Answers?** When summing hours or weights across `10^5` items, standard `int` overflows.
- [ ] **Did you use integer ceiling division?** Write `(a + b - 1) / b` instead of `ceil((double)a / b)` to avoid float precision bugs.
- [ ] **Did you pick the right 2D starting corner?** Start at Top-Right `(0, n - 1)` or Bottom-Left `(m - 1, 0)`, never Top-Left `(0, 0)`.
