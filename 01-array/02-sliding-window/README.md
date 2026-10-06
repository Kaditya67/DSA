# Sliding Window Pattern

## What Problem Does Sliding Window Solve?

Imagine you have an array of `N` elements and you need to find the maximum sum of any contiguous subarray of size `K`.

The naive way:
- Check subarray starting at index 0 (indices 0 to `K-1`) -> calculate sum
- Check subarray starting at index 1 (indices 1 to `K`) -> calculate sum
- Repeat until index `N - K`

> [!CAUTION]
> This requires `(N - K + 1) * K` additions.  
> If `K` is large (like `N / 2`), this blows up to **O(N^2)** time—leading directly to **Time Limit Exceeded (TLE)**!

Look closely at what happens when you move from index 0 to index 1:

```text
Subarray 1: [ A,  B,  C,  D ]
Subarray 2:     [ B,  C,  D,  E ]
```

Elements `B, C, D` were added twice! In fact, almost the entire subarray was already summed.  
Instead of recalculating from scratch:
1. **Subtract** the element that went out of scope (`A`)
2. **Add** the new element that entered the window (`E`)

Now each step takes strictly **O(1)** work instead of `O(K)`.  
Over the entire array, total runtime drops to **O(N)**.

---

## The Two Core Variants

### 1. Fixed Window Size

The length of the window is predetermined (`K`). The window slides from left to right like a camera viewfinder of constant width.

#### The Pattern
1. Precompute the state for the first window from index `0` to `K - 1`.
2. Loop `i` from `K` to `N - 1`:
   - Add incoming element: `arr[i]`
   - Remove outgoing element: `arr[i - K]`
   - Update your running answer.

#### Basic Skeleton
```cpp
// 1. Build initial window of size K
int window_sum = 0;
for (int i = 0; i < k; i++) {
    window_sum += arr[i];
}
int max_sum = window_sum;

// 2. Slide window across the rest of the array
for (int i = k; i < n; i++) {
    window_sum += arr[i] - arr[i - k];
    max_sum = max(max_sum, window_sum);
}
```

#### Where You See This
- **Maximum / Minimum sum** subarray of size `K`
- **First negative number** in every window of size `K`
- **Count occurrences of anagrams** in a fixed-size window

---

### 2. Variable Window Size (Dynamic Window)

The window expands and contracts dynamically. You do not know the size in advance.  
You are searching for the **longest** or **shortest** contiguous subarray satisfying a condition.

> [!IMPORTANT]
> **The Golden Rule of Variable Windows:**  
> - **Expand with `right`:** Stretch the window forward until the condition is met (or violated).  
> - **Shrink with `left`:** Pull the back boundary forward once the window becomes invalid (or optimal) until validity is restored.

#### Mental Model: The Rubber Band
- Stretch the rubber band forward (`right++`).
- When the tension gets too high (rule violated), pull the tail forward (`left++`) until it's safe again.

#### Skeleton: Finding Longest Valid Window
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

#### Skeleton: Finding Shortest Subarray (e.g. Sum >= Target)
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

## When Does Sliding Window FAIL?

> [!WARNING]
> Sliding Window relies strictly on **monotonicity**:  
> - Adding an element must **only increase** (or never decrease) your window property.  
> - Removing an element must **only decrease** (or never increase) it.  
>
> If an array has **negative numbers**:  
> - Adding a negative number makes the sum *smaller*.  
> - Removing a negative number makes the sum *larger*.  
> - Monotonicity breaks completely!  
>
> **The Rule:** If an array contains negative numbers and asks for subarray sum targets, **Sliding Window fails**. Use **Prefix Sum + HashMap** instead.

---

## How to Recognize Sliding Window in an Interview

1. **Contiguous constraint:**  
   The problem specifies a contiguous **subarray** or **substring** (never subsequences).
2. **Key trigger phrases:**  
   - *"Subarray of size K"*
   - *"Longest substring without repeating characters"*
   - *"Shortest subarray with sum at least S"*
   - *"At most K distinct elements"*
3. **Monotonic behavior:**  
   All elements are non-negative when dealing with sum-based constraints.
