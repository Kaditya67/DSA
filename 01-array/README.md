# Array Patterns: Quick Reference

A practical cheatsheet for the four essential array patterns. When you see an array problem, use this page to spot the pattern in under 30 seconds and avoid the common traps.

---

## 1. How to Pick Your Pattern

Ask yourself these three diagnostic questions:

1. **Does order matter?**
   - If the array is sorted (or can be sorted), and you need pairs/triplets $\to$ **Two-Pointer**
2. **Is it about contiguous subarrays?**
   - Maximum or minimum sum/product? $\to$ **Kadane's Algorithm**
   - Window size given, or longest/shortest with non-negative numbers? $\to$ **Sliding Window**
   - Sum equals `K`, multiples of `K`, or negative numbers present? $\to$ **Prefix Sum (+ Hash Map)**
3. **Do you need in-place modifications?**
   - Removing elements, shifting zeroes, Dutch Flag $\to$ **Two-Pointer (Fast & Slow / 3-Pointer)**

---

## 2. Comparison Matrix

| Pattern | Input Signal | When to Use | Time | Space |
|:---|:---|:---|:---:|:---:|
| **[01. Two-Pointer](./01-two-pointer/README.md)** | Sorted array, pair targets, in-place partitions | Two Sum II, 3Sum, Container Most Water, Dutch Flag | `O(N)` | `O(1)` |
| **[02. Sliding Window](./02-sliding-window/README.md)** | Contiguous, size `K`, longest/shortest with positive numbers | Max sum of size `K`, longest substring without repeat | `O(N)` | `O(1)` to `O(K)` |
| **[03. Prefix Sum](./03-prefix-sum/README.md)** | Range queries, sum = `K`, arrays with negative values | Range sum queries, subarray sum equals `K`, equal 0s & 1s | `O(1)` query / `O(N)` build | `O(N)` |
| **[04. Kadane's Algorithm](./04-kadanes-algorithm/README.md)** | Contiguous max/min sum, mixed positive & negative values | Maximum subarray sum, circular max subarray | `O(N)` | `O(1)` |

---

## 3. Visual Decision Tree

```text
Problem asks for an answer over an array:
│
├── Looking for pairs, triplets, palindrome, or in-place partition?
│   └── 01. Two-Pointer
│       ├── Converging: left -> <- right (Two Sum II, 3Sum)
│       ├── Fast & Slow: reader-writer (Remove duplicates, Move zeroes)
│       └── 3-Pointer: Dutch National Flag (Sort Colors)
│
└── Looking at CONTIGUOUS subarrays?
    │
    ├── Max / Min sum or product?
    │   └── 04. Kadane's Algorithm (Extend vs Restart backpack choice)
    │
    ├── Subarray of size K, or longest/shortest with positive growth?
    │   └── 02. Sliding Window (Expand right, shrink left)
    │
    └── Exact sum = K, divisible by K, or negatives break monotonicity?
        └── 03. Prefix Sum + Hash Map (S_j = S_i - K lookup)
```

---

## 4. Code Blueprints

### Two-Pointer (Converging)
```cpp
int left = 0, right = n - 1;
while (left < right) {
    int sum = arr[left] + arr[right];
    if (sum == target) return {left, right};
    (sum < target) ? left++ : right--;
}
```

### Sliding Window (Variable Size)
```cpp
int left = 0, max_len = 0;
for (int right = 0; right < n; right++) {
    add_to_state(arr[right]);
    while (is_invalid()) {
        remove_from_state(arr[left++]);
    }
    max_len = max(max_len, right - left + 1);
}
```

### Prefix Sum + Hash Map
```cpp
unordered_map<int, int> seen;
seen[0] = 1; // Base case: accounts for subarrays starting at index 0
int current_sum = 0, count = 0;

for (int num : nums) {
    current_sum += num;
    if (seen.count(current_sum - k)) {
        count += seen[current_sum - k];
    }
    seen[current_sum]++;
}
```

### Kadane's Algorithm
```cpp
int current_sum = nums[0];
int max_so_far = nums[0]; // Never initialize with 0!

for (size_t i = 1; i < nums.size(); i++) {
    current_sum = max(nums[i], current_sum + nums[i]);
    max_so_far = max(max_so_far, current_sum);
}
```

---

## 5. Quick Traps Checklist

Before you write code in an interview, verify these:

- [ ] **Are there negative numbers?**  
  If yes, **Sliding Window fails** for sum targets. Switch to **Prefix Sum + Hash Map**.
- [ ] **Did you initialize Prefix Sum map with `0: 1`?**  
  Without `seen[0] = 1`, you miss subarrays that start at index `0`.
- [ ] **Did you initialize Kadane with `nums[0]`?**  
  If the array is `[-5, -2, -8]` and you initialized with `0`, you return `0` instead of `-2`.
- [ ] **Are duplicate elements handled?**  
  In 3Sum or pair counting, skip duplicate elements (`while (left < right && arr[left] == arr[left+1]) left++`) after recording a valid answer.
- [ ] **Is modulo arithmetic safe?**  
  In C++ and Java, `-7 % 5 = -2`. For subarray sum divisible by `K`, always write `((sum % k) + k) % k`.
