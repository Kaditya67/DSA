# Kadane’s Algorithm Pattern

## The Problem
Given an integer array (containing both positive and negative numbers), find the **contiguous subarray** which has the **maximum sum**, and return that sum.

Example:
`arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`
The contiguous subarray with the largest sum is `[4, -1, 2, 1]`, with sum = `6`.

---

## Why Brute Force Is Wasteful
- Brute force checks all pairs `(i, j)` and sums elements from index `i` to `j`: $O(N^3)$ or $O(N^2)$ with running sum.
- For $N = 10^5$, this will fail immediately with TLE.

Kadane's algorithm computes this in a single pass: $O(N)$ time and $O(1)$ auxiliary space.

---

## The Core Intuition: The "Baggage" Analogy
Imagine you are walking along the array from left to right, collecting numbers in your backpack (`current_sum`):
- As long as what you are carrying in your backpack is positive (even if small), adding it to the next number `arr[i]` makes `arr[i]` bigger than `arr[i]` would be alone.
- But if the contents of your backpack drop below zero (`current_sum < 0`), carrying it into the next step will only **drag down** the next number.
- At that point, you throw away the backpack! You start fresh from the current number `arr[i]`.

### The Decision at Every Step
At index `i`, you have only two choices:
1. **Extend**: Add `arr[i]` to the running subarray (`current_sum + arr[i]`).
2. **Start fresh**: Discard the previous subarray and start a new one from `arr[i]`.

Mathematically, Dynamic Programming choice:
$$\text{current\_sum} = \max(\text{arr}[i], \text{current\_sum} + \text{arr}[i])$$

And you keep track of the maximum value ever reached:
$$\text{max\_so\_far} = \max(\text{max\_so\_far}, \text{current\_sum})$$

---

## Clean Implementation

```cpp
int maxSubArray(vector<int>& nums) {
    int current_sum = nums[0];
    int max_so_far = nums[0];

    for (size_t i = 1; i < nums.size(); i++) {
        // Either append nums[i] to current sum, or start fresh at nums[i]
        current_sum = max(nums[i], current_sum + nums[i]);

        // Record the overall peak seen so far
        max_so_far = max(max_so_far, current_sum);
    }

    return max_so_far;
}
```

---

## How to Print the Subarray Itself
Interviewers often say: *"Great, now also return the actual subarray, not just the sum."*
All you need is to track when you restart and when you update the maximum:

```cpp
vector<int> getMaxSubArray(vector<int>& nums) {
    int current_sum = nums[0];
    int max_so_far = nums[0];
    int start = 0, end = 0, temp_start = 0;

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > current_sum + nums[i]) {
            current_sum = nums[i];
            temp_start = i; // starting a new subarray
        } else {
            current_sum += nums[i];
        }

        if (current_sum > max_so_far) {
            max_so_far = current_sum;
            start = temp_start;
            end = i;
        }
    }

    return vector<int>(nums.begin() + start, nums.begin() + end + 1);
}
```

---

## Common Interview Variants

### 1. Maximum Circular Subarray Sum
What if the array wraps around (the last element connects to the first)?
A circular subarray maximum can be formed in two ways:
- **Case 1: Standard non-wrapping subarray**: Solved directly by standard Kadane's algorithm (`max_normal`).
- **Case 2: Wrapping subarray**: The maximum circular sum wraps around the ends. That means the elements *not* included form a contiguous **minimum subarray** in the middle!
  $$\text{max\_circular} = \text{total\_sum} - \text{min\_subarray\_sum}$$

**Result:** $\max(\text{max\_normal}, \text{total\_sum} - \text{min\_subarray\_sum})$.
*Crucial edge case*: If all numbers are negative, `total_sum == min_subarray_sum`, which yields `0`. If all numbers are negative, return `max_normal`.

---

### 2. Maximum Subarray Product
When multiplying, negative times negative becomes positive. A very small negative number can turn into the largest positive number on the very next step.
Kadane’s must be adapted to track two states at every step:
- `max_prod`: The maximum product ending here.
- `min_prod`: The minimum product ending here (most negative).

When `arr[i] < 0`, you swap `max_prod` and `min_prod` before updating.

---

## The Most Common Mistake to Avoid
**Initializing with 0:**
```cpp
// BUG: If arr = [-5, -2, -8], this will return 0, which is WRONG!
int max_so_far = 0;
```
If all elements in the array are negative, the answer is the largest single negative number (e.g. `-2`).
**Always** initialize `current_sum = nums[0]` and `max_so_far = nums[0]`.

