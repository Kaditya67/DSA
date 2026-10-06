# Prefix Sum Pattern

## Why Brute Force Fails First?

Suppose you are given an array of size `N`:
```text
Index:   0   1   2   3   4
Array: [ 3,  1,  4,  1,  5 ]
```
And an online judge asks you `100,000` queries like:
- *"What is the sum from index 1 to index 4?"*
- *"What is the sum from index 0 to index 3?"*

The naive way:
- For every query, run a `for` loop from index `L` to `R` and add elements up one by one.
- Each query takes up to `O(N)` time.

> [!CAUTION]
> If you have `Q = 10^5` queries and `N = 10^5` elements:  
> Total operations = `Q * N = 10^10` operations!  
> That is an immediate **Time Limit Exceeded (TLE)** on any online judge.

Prefix Sum drops every single range query down from `O(N)` to strictly **O(1)**.  
How? Let's break it down.

---

## What Enables This Technique?

Instead of summing the same numbers over and over again across queries:
- Precompute running cumulative totals **once** in `O(N)` time.
- Store them in an array called `pref`.

```text
Index:     0   1   2   3   4
arr:     [ 3,  1,  4,  1,  5 ]
pref:    [ 3,  4,  8,  9, 14 ]
```

Notice what `pref[i]` represents:
- `pref[0] = arr[0] = 3`
- `pref[1] = arr[0] + arr[1] = 4`
- `pref[2] = arr[0] + arr[1] + arr[2] = 8`
- `pref[i]` is simply the total sum from index `0` up to index `i`.

---

## How It Works: The Range Query Formula

Now, how do you find the sum between any `L` and `R` in `O(1)`?
- `pref[R]` gives you the sum from index `0` to `R`.
- `pref[L - 1]` gives you the sum from index `0` to `L - 1` (the left part you want to discard).

> [!IMPORTANT]
> **The Golden Formula:**  
> `Sum(L ... R) = pref[R] - pref[L - 1]`  
> *(If `L == 0`, there is nothing to discard on the left, so `Sum(0 ... R) = pref[R]`)*

### Basic Skeleton
```cpp
// Step 1: Precompute prefix sums in O(N)
vector<int> pref(n);
pref[0] = arr[0];
for (int i = 1; i < n; i++) {
    pref[i] = pref[i - 1] + arr[i];
}

// Step 2: Answer any range query [L, R] in strictly O(1)
int range_sum = (L == 0) ? pref[R] : pref[R] - pref[L - 1];
```

---

## The Killer Application: Subarray Sum Equals K (With Negatives)

This is the classic interview problem where Prefix Sum shines brightest.

### The Problem
Given an integer array (containing positive numbers, negative numbers, and zeros), count the total number of contiguous subarrays that sum up to `K`.

### Why Sliding Window Fails Here
- In Sliding Window, expanding `right` must always grow the sum, and shrinking `left` must always reduce the sum.
- When an array has **negative numbers**, adding a number can decrease the sum, and removing a number can increase it. Monotonicity is destroyed!

### The Prefix Sum + Hash Map Breakthrough
Let:
- `S_i` = prefix sum from start up to current index `i`
- `S_j` = prefix sum from start up to some earlier index `j` (where `j < i`)

The sum of the subarray strictly between `j + 1` and `i` is:
```text
subarray_sum = S_i - S_j
```

We want this subarray sum to equal `K`:
```text
S_i - S_j = K   =>   S_j = S_i - K
```

> [!IMPORTANT]
> **Mental Model (In Plain English):**  
> As you walk through the array carrying running sum `S_i`, ask:  
> *"Have I seen a prefix sum equal to `(S_i - K)` earlier? If yes, how many times?"*  
> Every time `(S_i - K)` appeared earlier, the subarray between that past point and your current index adds up to exactly `K`!

### Basic Skeleton
```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefix_counts;
    // Base case: empty prefix before array starts has sum 0 with count 1
    prefix_counts[0] = 1;

    int current_sum = 0;
    int total_subarrays = 0;

    for (int num : nums) {
        current_sum += num;

        // Check if an earlier prefix exists that leaves remainder k
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

## Traps to Avoid

> [!WARNING]
> 1. **Forgetting `prefix_counts[0] = 1`:**  
>    Suppose `nums = [3]` and target `K = 3`.  
>    - `current_sum = 3`  
>    - `needed = current_sum - K = 3 - 3 = 0`  
>    If `0` is not in the map initially with count `1`, you will miss the subarray `[3]` itself! `prefix_counts[0] = 1` accounts for subarrays starting right at index 0.
>
> 2. **Integer Overflow:**  
>    When summing large numbers over `10^5` elements, the cumulative sum can easily exceed the 32-bit signed integer limit (`2 * 10^9`). In C++ use `long long`, and in Java use `long`.
>
> 3. **Negative Modulo in "Divisible by K" Problems:**  
>    In C++ and Java, `%` with negative numbers returns a negative remainder (`-7 % 5 = -2`).  
>    Always normalize remainder modulo `K`:  
>    `rem = ((current_sum % k) + k) % k;`

---

## Clever Variations of Prefix Sum

### 1. Subarray with Equal Number of 0s and 1s
- Replace every `0` with `-1`
- Now finding a subarray with equal 0s and 1s is equivalent to finding a subarray with **sum = 0**!
- Store the *first occurrence* index of each prefix sum in a hash map to find the maximum length: `max_len = max(max_len, i - first_seen[current_sum])`.

### 2. Subarray Sum Divisible by K
- If `(S_i - S_j) % K == 0`, then mathematically:  
  `S_i % K == S_j % K`
- Instead of tracking raw sums, track remainder frequencies: `prefix_mod[rem]`. If the same remainder repeats, the subarray between them is divisible by `K`.

---

## How to Recognize Prefix Sum in an Interview

1. **Repeated Range Queries:**  
   Multiple queries asking for the sum, product, or parity over any range `[L, R]`.
2. **Subarray Sum Equals K (Especially with Negatives):**  
   Whenever a problem asks for contiguous subarrays summing to `K` or divisible by `K`, and the array contains negative numbers (or sliding window is impossible).
3. **Difference Array / Range Updates:**  
   Problems asking to add a value `val` to range `[L, R]` across multiple operations, then return the final array (Prefix sum on difference array).
