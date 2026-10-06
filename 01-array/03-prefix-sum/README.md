# Prefix Sum Pattern

## The Fundamental Intuition

Suppose someone gives you an array:
```text
Index:   0   1   2   3   4
Array: [ 3,  1,  4,  1,  5 ]
```
And asks you 100,000 queries like: *"What is the sum from index 1 to index 4?"*

If you sum elements one by one for every query, each query takes up to `O(N)` time.  
For `Q` queries, that is `O(Q * N)` total time.  
For `Q = 10^5` and `N = 10^5`, that is `10^10` operations—instant **Time Limit Exceeded (TLE)**!

Prefix Sum solves this by asking:  
**Can we precalculate running totals once, so that any range sum query takes strictly O(1) time?**

---

## How It Works

Create a new array `pref` where `pref[i]` stores the sum of all elements from index `0` up to `i`:

```text
Index:     0   1   2   3   4
arr:     [ 3,  1,  4,  1,  5 ]
pref:    [ 3,  4,  8,  9, 14 ]
```

Now, what is the sum of the subarray from index `L` to `R`?
- `pref[R]` gives the sum from index `0` to `R`.
- `pref[L - 1]` gives the sum from index `0` to `L - 1` (the left portion we cut off).
- Therefore:
  `Sum(L ... R) = pref[R] - pref[L - 1]`
- If `L == 0`, then `Sum(0 ... R) = pref[R]`.

### Precomputation Skeleton
```cpp
vector<int> pref(n);
pref[0] = arr[0];
for (int i = 1; i < n; i++) {
    pref[i] = pref[i - 1] + arr[i];
}

// Any range sum [L, R] in O(1):
int range_sum = (L == 0) ? pref[R] : pref[R] - pref[L - 1];
```

---

## The Killer Application: Subarray Sum Equals K (With Negatives)

This is where Prefix Sum turns into an essential interview tool.

### The Question
Given an array containing positive numbers, negative numbers, and zeros, find the number of contiguous subarrays that sum up to `K`.

### Why Sliding Window Fails Here
Because negative numbers exist, expanding the window does not guarantee the sum grows, and shrinking does not guarantee it shrinks. Monotonicity is broken.

### The Prefix Sum + Hash Map Breakthrough
Let `S_i` be the prefix sum up to index `i`, and `S_j` be the prefix sum up to index `j` (where `j < i`).  
The sum of the subarray between `j + 1` and `i` is:
```text
subarray_sum = S_i - S_j
```

We want this subarray sum to equal `K`:
```text
S_i - S_j = K   =>   S_j = S_i - K
```

> [!IMPORTANT]
> **In plain English:**  
> When we stand at index `i` with running prefix sum `S_i`, we ask:  
> *"Have we seen a previous prefix sum equal to `(S_i - K)` before? If yes, how many times?"*  
> Every time we previously saw `(S_i - K)`, the segment between that past index and our current index adds up to exactly `K`.

### Implementation
```cpp
int countSubarraysWithSumK(vector<int>& arr, int k) {
    unordered_map<int, int> prefix_counts;
    // Base case: a prefix sum of 0 has occurred once (before considering any elements)
    prefix_counts[0] = 1;

    int current_sum = 0;
    int total_subarrays = 0;

    for (int num : arr) {
        current_sum += num;

        // Check if there is a prefix sum that would leave remainder k
        int needed = current_sum - k;
        if (prefix_counts.find(needed) != prefix_counts.end()) {
            total_subarrays += prefix_counts[needed];
        }

        // Record the current prefix sum
        prefix_counts[current_sum]++;
    }

    return total_subarrays;
}
```

---

## Why Must You Initialize `prefix_counts[0] = 1`?

Consider `arr = [3]` and target `K = 3`.
- `current_sum = 3`.
- `needed = current_sum - K = 3 - 3 = 0`.

If `0` was not in the map with count 1, you wouldn't count the subarray `[3]` itself!  
`prefix_counts[0] = 1` represents the empty prefix before the array begins.

---

## Clever Variations of Prefix Sum

### 1. Equal 0s and 1s in a Binary Array
- Replace all `0`s with `-1`.
- Now, finding a subarray with equal 0s and 1s is equivalent to finding a subarray with a sum of `0`!
- Track prefix sums and store the first index where each prefix sum appeared in a hash map to find the longest subarray.

### 2. Subarray Sum Divisible by K
- If `(S_i - S_j) % K == 0`, then:
  `S_i % K == S_j % K`
- Track the remainder of prefix sums modulo `K`. If the same remainder repeats, the segment in between is divisible by `K`.
- Note for negatives: in C++ and Java, use `((rem % K) + K) % K` to avoid negative remainders.

---

## When to Reach for Prefix Sum
1. Repeated range queries (`L` to `R`).
2. Subarrays summing to `K`, multiples of `K`, or equal balance of two elements.
3. Arrays containing **negative numbers**, which rules out Sliding Window.
