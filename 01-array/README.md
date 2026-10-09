# Array Patterns: Quick Reference & Cheatsheet

A concise comparative reference for solving array problems. Use this guide to quickly diagnose which pattern applies, compare time/space trade-offs, and recall standard code skeletons during problem-solving or interview prep.

---

## 1. Pattern Decision Matrix

Use this quick-lookup table when reading a problem statement:

| Pattern | Input Requirements | Core Mechanism | When to Choose | Time Complexity | Auxiliary Space |
|:---|:---|:---|:---|:---:|:---:|
| **Two-Pointer** | Sorted array, or outward/inward scan | Two converging or directional indices | Pairs, triplets, palindrome checks, in-place partitions | `O(N)` (or `O(N log N)` with sort) | `O(1)` |
| **Sliding Window** | Contiguous elements, non-negative sums | Expand `right`, shrink `left` | Subarrays of fixed size `K`, longest/shortest satisfying condition | `O(N)` | `O(1)` or `O(K)` |
| **Prefix Sum** | Arbitrary numbers (positives, negatives, zeros) | Cumulative running sums: `pref[i] = pref[i-1] + arr[i]` | Repeated range queries `[L, R]`, subarray sum equals `K` | `O(1)` per query (`O(N)` build) | `O(N)` (array or hash map) |
| **Kadane's Algorithm** | Mixed numbers (positives & negatives) | Local choice: extend vs start fresh | Maximum / minimum contiguous subarray sum or product | `O(N)` | `O(1)` |

---

## 2. Decision Tree: Which Pattern to Use?

```text
Do you need an optimal contiguous subarray?
├── Maximum or minimum sum / product?
│   └── Kadane's Algorithm
│
├── Exact sum = K, divisible by K, or negatives present?
│   └── Prefix Sum (+ HashMap)
│
├── Window size K or longest/shortest with monotonic expansion?
│   └── Sliding Window
│
└── Pairs, triplets, partitioned elements, or sorted sequence?
    └── Two-Pointer
```

---

## 3. Pattern Skeletons at a Glance

### Two-Pointer (Opposite Ends)
```cpp
int left = 0, right = n - 1;
while (left < right) {
    int sum = arr[left] + arr[right];
    if (sum == target) {
        // match found
        break;
    } else if (sum < target) {
        left++;
    } else {
        right--;
    }
}
```

### Sliding Window (Variable Length - Longest Valid)
```cpp
int left = 0, max_len = 0;
for (int right = 0; right < n; right++) {
    add_to_state(arr[right]);
    while (is_invalid()) {
        remove_from_state(arr[left]);
        left++;
    }
    max_len = max(max_len, right - left + 1);
}
```

### Prefix Sum + Hash Map (Count Subarrays Sum = K)
```cpp
unordered_map<int, int> prefix_counts;
prefix_counts[0] = 1; // base case for subarrays starting at index 0
int current_sum = 0, count = 0;

for (int num : nums) {
    current_sum += num;
    int needed = current_sum - k;
    if (prefix_counts.count(needed)) {
        count += prefix_counts[needed];
    }
    prefix_counts[current_sum]++;
}
```

### Kadane's Algorithm (Maximum Subarray Sum)
```cpp
int current_sum = nums[0];
int max_so_far = nums[0];

for (size_t i = 1; i < nums.size(); i++) {
    current_sum = max(nums[i], current_sum + nums[i]);
    max_so_far = max(max_so_far, current_sum);
}
```

---

## 4. Key Traps & Pitfalls to Remember

> [!WARNING]
> - **Sliding Window with Negatives:** Fails because negative elements break monotonicity. Switch to **Prefix Sum + HashMap**.
> - **Prefix Sum Base Case:** Forgetting `prefix_counts[0] = 1` will miss valid subarrays that start from index `0`.
> - **Kadane Initialization:** Initializing `max_so_far = 0` produces wrong answers on arrays of all negative numbers. Always initialize with `nums[0]`.
> - **Two-Pointer Duplicates:** When counting unique triplets (e.g., 3Sum), remember to advance pointers past identical values to avoid duplicate sets.
> - **Modulo with Negatives:** In C++ and Java, `(-7 % 5)` yields `-2`. Always normalize remainders: `((val % k) + k) % k`.
