# Search in 2D Matrix Pattern

## Why Brute Force Fails First?

Suppose you have an `M x N` matrix (e.g., `1000 x 1000`) where numbers are sorted:
- A linear scan across all cells checks `M * N = 10^6` elements in `O(M * N)` time.
- If repeated across multiple queries or larger grids, this runs into TLE.

Because the matrix is sorted, we can search in **O(log(M * N))** or **O(M + N)** time using **O(1)** auxiliary space.

---

## The Two Matrix Problem Types

Matrix search problems fall into two distinct structural types:

```text
Type 1: Fully Sorted (Flattenable to 1D)
[  1,  3,  5,  7 ]
[ 10, 11, 16, 20 ]  <-- First element of row > last element of previous row
[ 23, 30, 34, 60 ]      Runs in O(log(M * N))

Type 2: Row-wise & Column-wise Sorted (Staircase Search)
[  1,  4,  7, 11, 15 ]
[  2,  5,  8, 12, 19 ]  <-- Rows are sorted left-to-right
[  3,  6,  9, 16, 22 ]      Columns are sorted top-to-bottom
[ 10, 13, 14, 17, 24 ]      Runs in O(M + N)
```

---

## 1. Type 1: Fully Sorted Matrix (LeetCode 74)

### The Mental Model
The entire matrix behaves like a single, flattened 1D sorted array of length `M * N`.
We can run **Standard 1D Binary Search** directly by mapping any 1D index `mid` to 2D coordinates `(row, col)`:

$$\text{row} = \text{mid} / N$$
$$\text{col} = \text{mid} \pmod N$$

### Blueprint: O(log(M * N))
```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    int low = 0, high = m * n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int r = mid / n;
        int c = mid % n;

        if (matrix[r][c] == target) {
            return true;
        } else if (matrix[r][c] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}
```

---

## 2. Type 2: Row-wise & Column-wise Sorted Matrix (LeetCode 240)

Here, the first element of row `i` is **not** necessarily larger than the last element of row `i - 1`. The matrix cannot be treated as a single sorted 1D array.

### The Staircase Search Mental Model
Start at a corner where decisions are uniquely deterministic:
- **Top-Right Corner `(0, N - 1)`** (or Bottom-Left):
  - Looking **left**: numbers strictly decrease.
  - Looking **down**: numbers strictly increase.

At any cell `(r, c)`:
- If `matrix[r][c] == target` $\to$ Found!
- If `matrix[r][c] > target` $\to$ Current number is too big. Nothing in this entire column can be the target. Move **left** (`c--`).
- If `matrix[r][c] < target` $\to$ Current number is too small. Nothing in this entire row to the left can be the target. Move **down** (`r++`).

### Blueprint: O(M + N)
```cpp
bool searchMatrixII(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    int r = 0, c = n - 1; // Start at top-right corner

    while (r < m && c >= 0) {
        if (matrix[r][c] == target) {
            return true;
        } else if (matrix[r][c] > target) {
            c--; // Target is smaller, eliminate current column
        } else {
            r++; // Target is larger, eliminate current row
        }
    }
    return false;
}
```

---

## Traps to Avoid

> [!WARNING]
> 1. **Starting at the Wrong Corner:** Do **not** start at Top-Left `(0, 0)` or Bottom-Right `(M - 1, N - 1)`. Moving either right or down from `(0, 0)` increases values, creating ambiguity. You must start at a corner where one direction increases and the other decreases (Top-Right or Bottom-Left).
> 2. **Integer Overflow on Total Cells:** If `M = 10^5` and `N = 10^5`, `m * n = 10^{10}`, which overflows 32-bit `int`. Use `long long` for `low`, `high`, and `mid` in Type 1 when total cells exceed `2 * 10^9`.

---

## How to Recognize Matrix Search in an Interview

1. **"Matrix is row-wise and column-wise sorted":** Staircase search starting at Top-Right `(0, n - 1)` in `O(M + N)`.
2. **"First integer of each row is greater than the last integer of the previous row":** 1D binary search mapping `mid / n` and `mid % n` in `O(log(M * N))`.
3. **K-th Smallest Element in Sorted Matrix:** Binary search on answers over range `[matrix[0][0], matrix[m-1][n-1]]` using Staircase count in `O(N * log(max - min))`.

