# Lower & Upper Bound Pattern

## Why Brute Force Fails First?

Suppose you have a sorted array with duplicate values:
`nums = [1, 2, 4, 4, 4, 4, 7, 9]`, target = `4`.

Problems often ask:
- *"What is the first occurrence of 4?"*
- *"What is the last occurrence of 4?"*
- *"Where should 5 be inserted to keep the array sorted?"*
- *"What is the floor (largest element <= target) or ceil (smallest element >= target)?"*

The naive way:
- Find any occurrence of `target` using classic binary search in `O(log N)`.
- Linearly scan left and right to find where duplicates start and end.

> [!CAUTION]
> If all `10^5` elements in the array are `4`, the linear scan across duplicates degrades your runtime from `O(log N)` back to **O(N)**!

Lower and Upper Bound patterns solve this in strictly **O(log N)** time by never stopping when `nums[mid] == target`, but rather continuing to narrow the boundary.

---

## The Definitions (STL Terminology)

1. **Lower Bound (`std::lower_bound`):**
   - The first index where `nums[index] >= target`.
   - Smallest index containing an element not less than target.
2. **Upper Bound (`std::upper_bound`):**
   - The first index where `nums[index] > target`.
   - Smallest index containing an element strictly greater than target.

---

## 1. Lower Bound Blueprint (`nums[i] >= target`)

When `nums[mid] >= target`:
- `mid` is a valid candidate.
- But could there be an even earlier valid candidate to the left? Yes!
- Record `ans = mid` and move left: `high = mid - 1`.

```cpp
int lowerBound(const vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    int ans = nums.size(); // Default if all elements are < target

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (nums[mid] >= target) {
            ans = mid;       // Candidate found
            high = mid - 1;  // Look for an earlier occurrence on the left
        } else {
            low = mid + 1;   // Too small, must look right
        }
    }
    return ans;
}
```

---

## 2. Upper Bound Blueprint (`nums[i] > target`)

When `nums[mid] > target`:
- `mid` is strictly greater than target.
- Record `ans = mid` and check if there is an earlier strictly greater element: `high = mid - 1`.

```cpp
int upperBound(const vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    int ans = nums.size(); // Default if all elements are <= target

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (nums[mid] > target) {
            ans = mid;       // Candidate strictly greater
            high = mid - 1;  // Look for an earlier one on the left
        } else {
            low = mid + 1;   // <= target, must look right
        }
    }
    return ans;
}
```

---

## Core Applications

### 1. First and Last Position of an Element (LeetCode 34)
To find the start and end range of `target`:
- `first_pos`: Use `lowerBound(nums, target)`. If `first_pos == nums.size()` or `nums[first_pos] != target`, target does not exist $\to$ return `{-1, -1}`.
- `last_pos`: Use `upperBound(nums, target) - 1`.

```cpp
vector<int> searchRange(vector<int>& nums, int target) {
    int first = lowerBound(nums, target);
    if (first == nums.size() || nums[first] != target) {
        return {-1, -1};
    }
    int last = upperBound(nums, target) - 1;
    return {first, last};
}
```

### 2. Search Insert Position (LeetCode 35)
Find the index where `target` should be inserted into a sorted array:
- This is literally the exact definition of `lowerBound(nums, target)`.

### 3. Floor and Ceil in a Sorted Array
- **Ceil** (smallest element `>= target`): `nums[lowerBound(nums, target)]`.
- **Floor** (largest element `<= target`): The index is `upperBound(nums, target) - 1`.

---

## Traps to Avoid

> [!WARNING]
> 1. **Default Answer Initialization:** If all elements are smaller than `target`, lower bound should return `nums.size()` (the insert position past the last element). Always initialize `ans = nums.size()`.
> 2. **Off-by-One on Last Occurrence:** Remember that `upperBound` gives the first index *greater* than target. The last index *equal* to target is `upperBound - 1`.
> 3. **Checking Bounds Before Access:** Always verify `first < nums.size() && nums[first] == target` before reading array values to avoid segmentation faults.

---

## How to Recognize Lower / Upper Bound in an Interview

1. **"First / Last occurrence" of an element.**
2. **"Search insert position" or maintaining a sorted collection.**
3. **"Count occurrences of target in a sorted array":**  
   `count = upperBound(target) - lowerBound(target)`.
4. **"Floor / Ceil" queries.**
