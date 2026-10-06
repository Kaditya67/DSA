# Sliding Window Pattern

## What Problem Does Sliding Window Solve?
Imagine you have an array of $N$ elements and you need to find the maximum sum of any contiguous subarray of size $K$.

The naive way:
- Check subarray starting at index 0 (indices 0 to $K-1$): calculate sum.
- Check subarray starting at index 1 (indices 1 to $K$): calculate sum.
- Repeat until index $N-K$.
This does $(N - K + 1) \times K$ additions. If $K$ is large (like $N/2$), this is $O(N^2)$ time.

Look closely at what happens when you move from index 0 to index 1:
```text
Subarray 1: [A, B, C, D]
Subarray 2:    [B, C, D, E]
```
Elements `B, C, D` were added twice. In fact, almost the entire subarray was already summed.
Instead of recalculating from scratch, you:
1. Subtract the element that went out of scope (`A`).
2. Add the new element that entered the window (`E`).
Now each move takes exactly $O(1)$ work instead of $O(K)$. Over the entire array, the runtime becomes $O(N)$.

---

## The Two Core Variants

### 1. Fixed Window Size
The length of the window is predetermined ($K$). The window slides from left to right like a camera viewfinder of constant width.

#### The Pattern
1. Precompute the state for the first window from index `0` to `K - 1`.
2. Loop `i` from `K` to `N - 1`:
   - Add incoming element: `arr[i]`
   - Remove outgoing element: `arr[i - K]`
   - Update your global answer.

#### Skeleton
```cpp
// 1. Build initial window
int window_sum = 0;
for (int i = 0; i < k; i++) {
    window_sum += arr[i];
}
int max_sum = window_sum;

// 2. Slide window
for (int i = k; i < n; i++) {
    window_sum += arr[i] - arr[i - k];
    max_sum = max(max_sum, window_sum);
}
```

#### Where You See This
- Maximum / Minimum sum subarray of size $K$
- First negative number in every window of size $K$
- Count occurrences of anagrams in a fixed-size window

---

### 2. Variable Window Size (Dynamic Window)
The window expands and contracts dynamically. You do not know the size in advance. You are looking for the longest or shortest contiguous subarray that satisfies some condition.

#### The Golden Rule of Variable Windows
- **Expand with `right`**: Make the window as large as needed by adding `arr[right]` until the condition is met (or violated).
- **Shrink with `left`**: Once the window becomes invalid (or optimal), advance `left` to restore validity or find the minimal length.

#### Mental Model: The Rubber Band
- You stretch the rubber band forward (`right++`).
- When the tension gets too high (condition broken), you pull the tail forward (`left++`) until the tension is safe again.

#### Skeleton (Finding Longest Valid Window)
```cpp
int left = 0;
int max_len = 0;

for (int right = 0; right < n; right++) {
    // 1. Expand: include arr[right] in current window state
    add_to_state(arr[right]);

    // 2. Contract: while current window violates rule, shrink from left
    while (is_invalid()) {
        remove_from_state(arr[left]);
        left++;
    }

    // 3. Current window [left ... right] is guaranteed valid
    max_len = max(max_len, right - left + 1);
}
```

#### Skeleton (Finding Shortest Subarray with Sum >= Target)
```cpp
int left = 0;
int min_len = INT_MAX;
int current_sum = 0;

for (int right = 0; right < n; right++) {
    current_sum += arr[right];

    // While condition is satisfied, record answer and try to shrink
    while (current_sum >= target) {
        min_len = min(min_len, right - left + 1);
        current_sum -= arr[left];
        left++;
    }
}
```

---

## When Does Sliding Window FAIL? (Important)
Sliding Window relies entirely on the fact that adding elements only increases the sum/property, and removing elements only decreases it.
- **Positive numbers only**: Adding numbers always makes the sum bigger. Removing numbers always makes it smaller. Sliding window works.
- **Negative numbers present**: If an array contains negative numbers, adding an element might make the sum smaller. Removing an element might make the sum bigger. You lose all monotonicity.
- When an array has negative numbers and asks for subarray sums, **Sliding Window fails**. You must use **Prefix Sum + HashMap** instead.

---

## Checklist to Spot Sliding Window
1. Does the problem specify a **contiguous** sequence (subarray or substring)? (If subsequences are allowed, this is not sliding window).
2. Does it use phrases like:
   - "Subarray of size $K$"
   - "Longest subarray such that..."
   - "Shortest subarray with sum at least..."
   - "At most $K$ distinct elements"
3. Are the elements non-negative (when sum-based)?

