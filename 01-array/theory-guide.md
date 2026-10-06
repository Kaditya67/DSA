# Array Pattern Theory & Comparative Guide

Arrays store elements in contiguous memory locations with $O(1)$ random index access. When solving array problems, the brute-force approach typically checks every pair or subarray in $O(N^2)$ or $O(N^3)$ time.

The four primary array patterns reduce time complexity to $O(N)$ or $O(N \log N)$ by exploiting specific structural properties: **order/monotonicity**, **contiguous boundaries**, **cumulative state**, and **local optimality**.

---

## Pattern Comparison Matrix

| Pattern | Input Requirements | Core Mechanism | Primary Target Questions | Time Complexity | Auxiliary Space |
|:---|:---|:---|:---|:---:|:---:|
| **Two-Pointer** | Sorted array, or inward/outward scanning | Converging or direction-matched indices | Pair/triplet sum, partitioning, palindrome, in-place removal | $O(N)$ (or $O(N \log N)$ if sorting required) | $O(1)$ |
| **Sliding Window** | Contiguous subarrays | Dynamic boundaries (`left`, `right`) | Subarray length with condition $\le K$, exactly $K$, fixed window max/min | $O(N)$ | $O(1)$ or $O(K)$ (with state table/map) |
| **Prefix Sum** | Arbitrary numbers (positives, negatives, zeros) | Cumulative sum array: $P[i] = \sum_{j=0}^{i-1} A[j]$ | Range sum queries $[L, R]$, subarray count with sum $= K$ | $O(1)$ per query ($O(N)$ precomputation) | $O(N)$ (or $O(N)$ hash table) |
| **Kadane's Algorithm** | Array containing mixed numbers (positives & negatives) | Local optimal choice: extend vs. restart | Maximum/minimum contiguous subarray sum / product | $O(N)$ | $O(1)$ |

---

## 1. Two-Pointer Pattern

### 1.1 Core Concept
Instead of iterating through nested loops ($i$ from $0$ to $N-1$, $j$ from $i+1$ to $N-1$), two pointers maintain two indices that navigate the sequence simultaneously based on comparison logic.

### 1.2 Variants
1. **Opposite Ends (Converging)**:
   - One pointer at `left = 0`, one at `right = n - 1`.
   - Used heavily on sorted arrays. If `arr[left] + arr[right] > target`, decrement `right` to decrease sum; if `< target`, increment `left`.
2. **Same Direction (Fast & Slow / Reader-Writer)**:
   - Both pointers start at index $0$.
   - `fast` explores ahead; `slow` records valid elements or maintains a slower threshold (e.g., removing duplicates in-place).
3. **Partitioning (Dutch National Flag / QuickSelect)**:
   - Three pointers: `low`, `mid`, `high` dividing the array into distinct sections ($< pivot$, $= pivot$, $> pivot$).

### 1.3 Trigger Signals
- Array is sorted (or can be sorted in $O(N \log N)$ without breaking required indices).
- Question asks for pairs, triplets, or reversals.
- In-place modifications without allocating extra arrays ($O(1)$ space constraint).

### 1.4 Pitfalls & Edge Cases
- Forgetting to handle duplicates when counting unique pairs/triplets (e.g., 3Sum).
- Off-by-one pointer convergence (`left < right` vs. `left <= right`).

---

## 2. Sliding Window Pattern

### 2.1 Core Concept
A window is defined by two pointers `[left, right]` representing a contiguous subarray. Instead of recomputing results for overlapping subarrays from scratch ($O(N \cdot K)$), you incrementally update the window state when:
- Expanding: include `arr[right]`.
- Shrinking: exclude `arr[left]`.

### 2.2 Variants
1. **Fixed Window Size ($K$)**:
   - Window size is constant.
   - Advance `right`. Once `right - left + 1 == K`, compute answer, then remove `arr[left]` and increment `left`.
2. **Variable Window Size (Dynamic)**:
   - Find longest/shortest subarray satisfying a condition.
   - Expand `right` until constraint is violated (or met), then contract `left` while updating the optimal window size.
3. **Exact Condition via Difference**:
   - Finding subarrays with **exactly** $K$ distinct elements is often calculated as:
     $$\text{Exactly}(K) = \text{AtMost}(K) - \text{AtMost}(K - 1)$$

### 2.3 Trigger Signals
- Contiguous subarray or substring explicitly mentioned.
- Questions asking for "longest", "shortest", "minimum length", or "at most $K$".

### 2.4 Pitfalls & Edge Cases
- Arrays with negative numbers break monotonicity. If array has negative elements, sliding window expansion does not guarantee sum growth; **Prefix Sum + HashMap** must be used instead.
- Empty arrays or $K > N$.

---

## 3. Prefix Sum Pattern

### 3.1 Core Concept
Precompute running totals so that any subarray sum from index $L$ to $R$ can be answered in $O(1)$:
$$\text{Sum}(L, R) = \text{prefix}[R] - \text{prefix}[L - 1]$$
where $\text{prefix}[i] = \text{prefix}[i-1] + \text{arr}[i]$ with base case $\text{prefix}[-1] = 0$.

### 3.2 Variants
1. **Static 1D / 2D Range Queries**:
   - Answering repeated interval sum queries efficiently.
2. **Prefix Sum + Hash Map (Target Sum $K$)**:
   - To find how many subarrays sum to $K$:
     $$\text{current\_sum} - \text{target} = \text{previous\_prefix\_sum}$$
   - Maintain a frequency map of previous prefix sums seen so far. If $(\text{current\_sum} - K)$ exists in the map, a valid subarray ends at the current index.
3. **Prefix State Transformation**:
   - Replace elements with $+1$ and $-1$ (e.g., contiguous subarrays with equal number of 0s and 1s) and look for identical prefix sums.

### 3.3 Trigger Signals
- Frequent range sum queries.
- Counting or locating subarrays with a specific target sum where **numbers can be negative**.
- Modulo constraints (e.g., subarray sum divisible by $K$, using $\text{prefix} \pmod K$).

### 3.4 Pitfalls & Edge Cases
- Always initialize the prefix hash map with `{0: 1}` to account for subarrays starting at index $0$.
- Integer overflow with large prefix sums in C++ and Java (use `long long` / `long`).

---

## 4. Kadane’s Algorithm Pattern

### 4.1 Core Concept
Kadane's algorithm finds the maximum subarray sum in $O(N)$ time and $O(1)$ space using dynamic programming optimization.

At each index $i$, determine whether to:
1. Extend the existing subarray: `current_sum + arr[i]`
2. Start a new subarray at `arr[i]`: `arr[i]`

State transition:
$$\text{current\_sum} = \max(\text{arr}[i], \text{current\_sum} + \text{arr}[i])$$
$$\text{max\_so\_far} = \max(\text{max\_so\_far}, \text{current\_sum})$$

### 4.2 Variants
1. **Maximum Subarray Sum**:
   - Standard Kadane's algorithm.
2. **Circular Subarray Maximum Sum**:
   - The maximum sum is either standard Kadane or the circular wrap-around:
     $$\text{max\_circular} = \text{total\_sum} - \text{min\_subarray\_sum}$$
   - *Special Case*: If all numbers are negative, return standard maximum (`total_sum - min_subarray_sum == 0`).
3. **Maximum Subarray Product**:
   - Because negative multiplied by negative yields positive, track both `max_prod` and `min_prod` at each step.

### 4.3 Trigger Signals
- Contiguous subarray optimization (maximum/minimum sum or product).
- Decisions boil down to "restart at current element or append to current segment".

### 4.4 Pitfalls & Edge Cases
- When all numbers in the array are negative, initializing `max_so_far = 0` produces wrong output. Always initialize `max_so_far = arr[0]`.

---

## Decision Framework: Which Pattern to Use?

```text
Do you need an optimal contiguous subarray?
├── Maximum or minimum sum/product?
│   └── Kadane's Algorithm
├── Condition involves sum = K, divisible by K, and array has negatives?
│   └── Prefix Sum (+ HashMap)
├── Condition involves window of size K, or longest/shortest with non-negative growth?
│   └── Sliding Window
└── Finding pairs/triplets, partitioned elements, or array is sorted?
    └── Two-Pointer
```
