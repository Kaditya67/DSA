# Two-Pointer Pattern

## Why Brute Force Fails First?

When you start solving array problems:
- The first instinct is almost always: run a loop for `i`
- Then run an inner loop for `j`

> [!CAUTION]
> For an array of size `N`, checking all pairs takes **O(N^2)** operations.  
> If `N = 10^5`, then `N^2 = 10^10` operations, which hits **Time Limit Exceeded (TLE)** on any online judge within 1 second!

The Two-Pointer technique drops this down to **O(N)**. How? Let's break it down.

---

## What Enables This Technique?

You cannot just throw two pointers at any random problem. It works **only** when the problem gives you a monotonic property:
- Moving a pointer in one direction strictly increases or decreases the value you are tracking.
- If the array is sorted:
  - Moving `left` to the right -> increases values.
  - Moving `right` to the left -> decreases values.

> [!IMPORTANT]
> **In short:** The array must be sorted, or capable of being sorted!  
> Because direction is predictable, you **never** need to backtrack or check combinations that mathematically cannot work.

---

## The Three Flavors of Two-Pointer

### 1. Opposite Ends (Converging Pointers)

You place one pointer at the start (`left = 0`) and one at the end (`right = n - 1`). They move toward each other until they meet.

#### Mental Model
Think of a balance scale:
- If current sum is too small -> you need bigger numbers. The only way is `left++`.
- If current sum is too large -> you need smaller numbers. The only way is `right--`.
- If it matches your target -> you found the answer!

#### Basic Skeleton
```cpp
int left = 0;
int right = n - 1;

while (left < right) {
    int current_sum = arr[left] + arr[right];
    if (current_sum == target) {
        // found pair
        break;
    } else if (current_sum < target) {
        left++;
    } else {
        right--;
    }
}
```

#### Where You See This
- **Two Sum II** (Input array is sorted)
- **3Sum** (Sort array first, fix one element with loop `i`, then run converging two-pointer on `left` and `right`)
- **Container With Most Water** (Move the pointer pointing to the shorter line)
- **Valid Palindrome**

---

### 2. Same Direction (Fast and Slow Pointers / Reader-Writer)

Both pointers start at the beginning of the array:
- `fast`: Reads every element in the array one by one.
- `slow`: Writes or holds the boundary of valid elements.

#### Mental Model
Think of cleaning a shelf:  
`fast` inspects every book on the shelf. If the book is not dusty (satisfies condition), you hand it to `slow` who places it at the front of the shelf, then `slow` takes one step forward.

#### Basic Skeleton
```cpp
int slow = 0;

for (int fast = 0; fast < n; fast++) {
    if (should_keep(arr[fast])) {
        arr[slow] = arr[fast];
        slow++;
    }
}
// Array from 0 to slow - 1 contains all valid elements in-place.
```

#### Where You See This
- **Remove Duplicates from Sorted Array**
- **Move Zeroes to End**
- **Remove Element in-place**

---

### 3. Three Pointers (Dutch National Flag Partitioning)

Instead of two pointers, you maintain three: `low`, `mid`, `high`.
- `[0 ... low-1]`: Region 1 (e.g., all 0s)
- `[low ... mid-1]`: Region 2 (e.g., all 1s)
- `[mid ... high]`: Unknown / Unprocessed region
- `[high+1 ... n-1]`: Region 3 (e.g., all 2s)

#### Basic Skeleton
```cpp
int low = 0, mid = 0, high = n - 1;

while (mid <= high) {
    if (arr[mid] == 0) {
        swap(arr[low], arr[mid]);
        low++;
        mid++;
    } else if (arr[mid] == 1) {
        mid++;
    } else { // arr[mid] == 2
        swap(arr[mid], arr[high]);
        high--;
        // Notice: do NOT increment mid here! The swapped element is unexamined.
    }
}
```

#### Where You See This
- **Sort Colors** (0s, 1s, and 2s)
- **QuickSort Partitioning** (pivot positioning)

---

## How to Recognize Two-Pointer in an Interview

1. **Look at constraints:**  
   If `N <= 10^5`, an **O(N^2)** solution will fail. You need **O(N)** or **O(N log N)**.
2. **Look at the data:**  
   Is the array sorted? Or can you sort it without breaking required indices?
3. **Look at the problem ask:**  
   Is it asking for pairs, triplets, reversals, partitions, or in-place modification with **O(1)** extra space?

---

## Traps to Avoid

> [!WARNING]
> 1. **Loop Termination:** Know whether your condition is `while (left < right)` or `while (left <= right)`. For pair problems, `left == right` means reusing the same element twice. Usually you want `left < right`.
> 2. **Handling Duplicates:** In problems like 3Sum, after finding a match, you must skip duplicate values for both `left` and `right` to avoid duplicate results.
> 3. **Unsorted Arrays Where Indices Matter:** If the question asks for original 1-based indices and you sort the array, you lose those positions. In that case, a **HashMap** is often the better choice.
