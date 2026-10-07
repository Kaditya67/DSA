# Kadane’s Algorithm Pattern

## Why Brute Force Fails First?

Suppose you are given an integer array with both positive and negative numbers:
```text
Index:   0   1   2   3   4   5   6   7   8
nums:  [-2,  1, -3,  4, -1,  2,  1, -5,  4]
```
And you need to find the **contiguous subarray** with the **maximum sum**.

The naive way:
- Check every starting index `i` from `0` to `N - 1`
- Check every ending index `j` from `i` to `N - 1`
- Calculate the sum of the subarray between `i` and `j`

> [!CAUTION]
> Checking all `(i, j)` pairs takes `O(N^2)` time (or `O(N^3)` without running sum).  
> If `N = 10^5`, that requires `10^10` operations—resulting in an immediate **Time Limit Exceeded (TLE)**!

Kadane's Algorithm solves this problem in a single pass: strictly **O(N)** time and **O(1)** auxiliary space.  
How? Let's break it down.

---

## What Enables This Technique?

Kadane's Algorithm is a dynamic programming optimization in disguise.  
At every index `i`, you do **not** need to look back at all previous subarrays. You only need to answer one local question:

> *"Is the previous subarray sum helping me, or is it dragging me down?"*

### The Backpack Analogy
Imagine walking through the array from left to right, collecting numbers in your backpack (`current_sum`):
- As long as what is inside your backpack is **positive** (`current_sum > 0`), adding it to the next number `nums[i]` makes `nums[i]` bigger than it would be alone.
- But the moment your backpack drops **below zero** (`current_sum < 0`), carrying it forward will only drag down whatever comes next.
- When that happens: **throw away the backpack!** Start fresh with `nums[i]` as the beginning of a brand-new subarray.

---

## The Decision at Every Step

At each element `nums[i]`, you have exactly two choices:
1. **Extend:** Add `nums[i]` to the running subarray (`current_sum + nums[i]`)
2. **Start fresh:** Discard the previous subarray and start a new one from `nums[i]`

> [!IMPORTANT]
> **The Core State Transitions:**  
> `current_sum = max(nums[i], current_sum + nums[i])`  
> `max_so_far  = max(max_so_far, current_sum)`

---

## Clean Implementation

```cpp
int maxSubArray(vector<int>& nums) {
    // Always initialize with the first element, NEVER with 0!
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

## Interview Follow-up: Printing the Subarray

Interviewers often ask: *"Great, now return the actual subarray itself, not just the sum."*  
To do this, track three indices:
- `start`: Start index of the best subarray found so far
- `end`: End index of the best subarray found so far
- `temp_start`: Candidate start index when starting fresh

```cpp
vector<int> getMaxSubArray(vector<int>& nums) {
    int current_sum = nums[0];
    int max_so_far = nums[0];
    int start = 0, end = 0, temp_start = 0;

    for (size_t i = 1; i < nums.size(); i++) {
        // If starting fresh is better, update candidate start index
        if (nums[i] > current_sum + nums[i]) {
            current_sum = nums[i];
            temp_start = i;
        } else {
            current_sum += nums[i];
        }

        // When a new global maximum is reached, lock in start and end
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
A circular maximum subarray can form in two ways:
- **Case 1: Standard non-wrapping subarray:** Solved directly by normal Kadane (`max_normal`).
- **Case 2: Wrapping subarray:** The subarray wraps around both ends. That means the elements *left out* form a contiguous **minimum subarray** in the middle!
  ```text
  max_circular = total_sum - min_subarray_sum
  ```

**Result:** `max(max_normal, total_sum - min_subarray_sum)`.  
*(Special Edge Case: If all elements are negative, `total_sum == min_subarray_sum`, giving `0`. In this case, return `max_normal`).*

### 2. Maximum Subarray Product
When multiplying numbers, multiplying two negatives yields a positive. A large negative number can instantly become the largest positive number on the very next step.  
Kadane's must track **two states** at every step:
- `max_prod`: Maximum product ending at the current index
- `min_prod`: Minimum product ending at the current index (most negative)

When `nums[i] < 0`, swap `max_prod` and `min_prod` before computing!

---

## Traps to Avoid

> [!WARNING]
> 1. **Initializing with 0:**  
>    ```cpp
>    // BUG: If nums = [-5, -2, -8], this will return 0, which is WRONG!
>    int max_so_far = 0;
>    ```
>    If all numbers in the array are negative, the correct answer is the least negative number (e.g., `-2`). **Always** initialize `current_sum = nums[0]` and `max_so_far = nums[0]`.
>
> 2. **Empty Subarray Assumption:**  
>    Clarify with the interviewer whether an empty subarray (sum = 0) is allowed. If empty subarrays are allowed, the answer for all-negative inputs is `0`. If non-empty is required, the answer is `max(nums)`.
>
> 3. **Non-Contiguous Confusion:**  
>    Kadane's applies **strictly to contiguous subarrays**. If elements can be chosen non-contiguously (subsequences), the problem reduces to simply summing all positive numbers, which is greedy, not Kadane.

---

## How to Recognize Kadane’s Algorithm in an Interview

1. **Subarray optimization:**  
   The problem asks for the maximum (or minimum) sum or product of a contiguous subarray.
2. **Mixed positive and negative values:**  
   The array contains both positive and negative values, making simple greedy or two-pointer techniques inapplicable.
3. **Local restart choice:**  
   The decision at every step simplifies to: *"append to current segment vs. start fresh at current element"*.
