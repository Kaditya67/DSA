# Classic Binary Search Pattern

## Why Brute Force Fails First?

Suppose you need to locate an element in a sorted list of `N = 10^9` items:
- A linear scan checks elements one by one from index `0` to `N - 1`.
- In the worst case, it takes `10^9` operations—instant **Time Limit Exceeded (TLE)**!

Because the data is sorted, every single comparison tells you which entire half of the array cannot contain the answer.
- Classic Binary Search halves the search space at each step: `N -> N/2 -> N/4 -> ... -> 1`.
- It takes at most `log2(10^9) ≈ 30` comparisons!
- That is **O(log N)** time using **O(1)** auxiliary space.

---

## What Enables This Technique?

Binary Search works **only** when your search space exhibits **monotonicity**:
- Elements are sorted (ascending or descending).
- Or a property evaluates to `[False, False, ..., False, True, True, ...]`.

Because the data is ordered:
- If `target > nums[mid]`, the target *cannot* exist in the left half `[low ... mid]`. Discard it.
- If `target < nums[mid]`, the target *cannot* exist in the right half `[mid ... high]`. Discard it.

---

## The Standard Blueprint

```cpp
int binarySearch(const vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high) {
        // Prevent 32-bit integer overflow: never write (low + high) / 2
        int mid = low + (high - low) / 2;

        if (nums[mid] == target) {
            return mid; // Target found
        } else if (nums[mid] < target) {
            low = mid + 1; // Discard left half
        } else {
            high = mid - 1; // Discard right half
        }
    }

    return -1; // Target does not exist
}
```

---

## Key Variations of Classic Binary Search

### 1. Rotated Sorted Array (Search in Rotated Sorted Array)
An array like `[4, 5, 6, 7, 0, 1, 2]` is divided into two sorted segments.
- Even when rotated, **at least one half `[low ... mid]` or `[mid ... high]` is guaranteed to be strictly sorted**!
- Check which half is normally sorted:
  1. If `nums[low] <= nums[mid]`, the **left half** is sorted.
     - Check if `target` lies within `nums[low] <= target < nums[mid]`. If yes, search left (`high = mid - 1`); else search right (`low = mid + 1`).
  2. Otherwise, the **right half** is sorted.
     - Check if `target` lies within `nums[mid] < target <= nums[high]`. If yes, search right (`low = mid + 1`); else search left (`high = mid - 1`).

```cpp
int searchRotated(const vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;

        if (nums[low] <= nums[mid]) { // Left half is sorted
            if (nums[low] <= target && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else { // Right half is sorted
            if (nums[mid] < target && target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}
```

### 2. Find Minimum in Rotated Sorted Array
Compare `nums[mid]` against `nums[high]`:
- If `nums[mid] > nums[high]`, the inflection point (minimum) must be strictly in the right half $\to$ `low = mid + 1`.
- If `nums[mid] <= nums[high]`, the minimum is at `mid` or to its left $\to$ `high = mid`.

---

## Traps to Avoid

> [!WARNING]
> 1. **Integer Overflow:** Writing `(low + high) / 2` causes integer overflow when `low + high > 2^31 - 1`. Always write `low + (high - low) / 2`.
> 2. **Loop Condition (`<=` vs `<`):**  
>    - When search space includes both endpoints `[low, high]`, use `while (low <= high)`.
>    - When shrinking down to a single candidate index (like finding a pivot or bound), use `while (low < high)`.
> 3. **Duplicates in Rotated Arrays:** If `nums[low] == nums[mid] == nums[high]`, you cannot tell which half is sorted. You must shrink both ends (`low++`, `high--`), dropping worst-case time to `O(N)`.

---

## How to Recognize Classic Binary Search in an Interview

1. **Explicit sorted order:** Problem statement explicitly states the array is sorted (or rotated sorted).
2. **Strict time bound:** Constraints demand `O(log N)` runtime for search queries.
3. **Lookup or pivot detection:** Finding an exact target, peak element, or pivot in an ordered collection.
