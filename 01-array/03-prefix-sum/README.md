# Prefix Sum Pattern

## The Fundamental Intuition

Suppose someone gives you an array:
```text
Index:   0   1   2   3   4
Array: [ 3,  1,  4,  1,  5 ]
```
And asks you 100,000 queries like: *"What is the sum from index 1 to index 4?"*

If you sum elements one by one for every query:
- Each query takes up to `O(N)` time
- For `Q` queries, that is `O(Q * N)` total time
- For `Q = 10^5` and `N = 10^5`, that is `10^10` operations!

> [!CAUTION]
> Re-summing subarrays on every query results in **Time Limit Exceeded (TLE)**!

Prefix Sum asks:  
**Can we precalculate running totals once in O(N), so that every future range sum query takes strictly O(1)?**

---

## How It Works

Create a new array `pref` where `pref[i]` stores the sum of all elements from index `0` up to `i`:

```text
Index:     0   1   2   3   4
arr:     [ 3,  1,  4,  1,  5 ]
pref:    [ 3,  4,  8,  9, 14 ]
```

Now, what is the sum of the subarray from index `L` to `R`?
- `pref[R]` gives the total sum from index `0` to `R`
- `pref[L - 1]` gives the sum from index `0` to `L - 1` (the left part we want to cut off)

> [!IMPORTANT]
> **The Core Formula:**  
> `Sum(L ... R) = pref[R] - pref[L - 1]`  
> *(If `L == 0`, no left part to cut off: `Sum(0 ... R) = pref[R]`)*

### Precomputation Skeleton
```cpp
vector<int> pref(n);
pref[0] = arr[0];
for (int i = 1; i < n; i++) {
    pref[i] = pref[i - 1] + arr[i];
}

// Any range sum [L, R] in strictly O(1):
int range_sum = (L == 0) ? pref[R] : pref[R] - pref[L - 1];
```

---

## The Killer Application: Subarray Sum Equals K (With Negatives)

This is where Prefix Sum turns into an essential interview tool.

### The Problem
Given an array containing positive numbers, negative numbers, and zeros, find the number of contiguous subarrays that sum up to `K`.

### Why Sliding Window Fails Here
When negative numbers exist, expanding the window doesn't always increase the sum, and shrinking doesn't always decrease it. Monotonicity is broken.

### The Prefix Sum + Hash Map Breakthrough
Let:
- `S_i` = prefix sum up to current index `i`
- `S_j` = prefix sum up to an earlier index `j` (where `j < i`)

The sum of the subarray between `j + 1` and `i` is:
```text
subarray_sum = S_i - S_j
```

We want this subarray sum to equal `K`:
```text
S_i - S_j = K   =>   S_j = S_i - K
```

> [!IMPORTANT]
> **In Plain English:**  
> While standing at index `i` with current running sum `S_i`, ask:  
> *"Have we seen an earlier prefix sum equal to `(S_i - K)`? If yes, how many times?"*  
> Every time `(S_i - K)` appeared earlier, the subarray between that point and our current index adds up to exactly `K`!

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

        // Have we seen a prefix sum that leaves remainder k?
        int needed = current_sum - k;
        if (prefix_counts.find(needed) != prefix_counts.end()) {
            total_subarrays += prefix_counts[needed];
        }

        // Record the current prefix sum in our frequency map
        prefix_counts[current_sum]++;
    }

    return total_subarrays;
}
```

---

## Why Must You Initialize `prefix_counts[0] = 1`?

> [!WARNING]
> Consider `arr = [3]` and target `K = 3`:  
> - `current_sum = 3`  
> - `needed = current_sum - K = 3 - 3 = 0`  
>
> If `0` is not in the map with count `1`, you will miss the subarray `[3]` itself!  
> `prefix_counts[0] = 1` represents the empty prefix sum before the array begins.

---

## Clever Variations of Prefix Sum

### 1. Equal 0s and 1s in a Binary Array
- Replace every `0` with `-1`
- Now, finding a subarray with equal 0s and 1s is identical to finding a subarray with **sum = 0**!
- Store the *first occurrence* index of each prefix sum in a hash map to compute the longest subarray length: `max_len = max(max_len, i - first_seen[current_sum])`.

### 2. Subarray Sum Divisible by K
- If `(S_i - S_j) % K == 0`, then mathematically:  
  `S_i % K == S_j % K`
- Track the remainder of prefix sums modulo `K`. When the same remainder repeats, the subarray between them is a multiple of `K`.
- **Negative modulo fix:** in C++ and Java, `%` can yield negative remainders. Always normalize:  
  `rem = ((current_sum % K) + K) % K`

---

## When to Reach for Prefix Sum
1. Repeated range sum queries (`L` to `R`) $\to$ static array precomputation.
2. Contiguous subarrays with a target sum `K`, especially when the array contains **negative numbers**.
3. Parity or balancing problems (e.g. equal 0s and 1s) transformed using `+1` and `-1`.
