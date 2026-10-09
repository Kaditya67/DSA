# Binary Search on Answers Pattern

## Why Brute Force Fails First?

Consider these classic interview problems:
- *Koko Eating Bananas:* Find the minimum speed `k` to eat all bananas within `H` hours.
- *Capacity to Ship Packages:* Find the minimum ship capacity to ship all packages within `D` days.
- *Split Array Largest Sum:* Minimize the largest subarray sum when splitting into `M` parts.
- *Aggressive Cows / Book Allocation:* Maximize the minimum distance between placed elements.

The naive way:
- Try every possible speed or capacity starting from `1` up to the maximum possible value: `speed = 1, 2, 3, ...`
- For each speed, simulate the process across the array in `O(N)` time.
- If the maximum capacity is `10^9`, this takes `10^9 * N` operations $\to$ **Time Limit Exceeded (TLE)**!

Binary Search on Answers optimizes this search from `O(Max * N)` to strictly **O(N * log(Max))**.

---

## What Enables This Technique?

You are not searching for an element inside an array.  
You are searching for the **optimal value within an answer range `[low, high]`**.

What makes it possible is the **Monotonic Predicate Function `isValid(mid)`**:
- If speed `mid` is feasible, then any speed **greater than `mid`** is also feasible:  
  `[False, False, False, True, True, True, True]`
- If speed `mid` is too slow, then any speed **less than `mid`** is definitely too slow.

Because the feasibility function transitions monotonically from `False` to `True` (or `True` to `False`), we can binary search the boundary!

---

## The Master Blueprint

Every Binary Search on Answers problem follows this exact 3-step template:

```cpp
// Step 1: Define the feasibility check
bool isFeasible(const vector<int>& nums, int mid, int constraint) {
    // Return true if 'mid' satisfies the problem constraint in O(N) time
}

// Step 2: Binary Search over the answer range [low, high]
int binarySearchOnAnswer(const vector<int>& nums, int constraint) {
    int low = getMinPossibleAnswer();
    int high = getMaxPossibleAnswer();
    int ans = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isFeasible(nums, mid, constraint)) {
            ans = mid;        // 'mid' works, record candidate
            high = mid - 1;   // For minimization: try to find a smaller feasible value
            // (For maximization: low = mid + 1)
        } else {
            low = mid + 1;    // 'mid' is impossible, increase value
            // (For maximization: high = mid - 1)
        }
    }

    return ans;
}
```

---

## Walkthrough: Koko Eating Bananas (LeetCode 875)

**Problem:** Piles of bananas `piles`, must eat all within `h` hours. Find the minimum integer eating speed `k` per hour.

1. **Answer Range:**
   - Minimum possible speed: `low = 1` (cannot eat 0 bananas/hr).
   - Maximum possible speed: `high = max(piles)` (eating more than the largest pile in 1 hour is pointless).
2. **Feasibility Function:**
   - For speed `k`, hours taken for a pile is `ceil(pile / k) = (pile + k - 1) / k`.
   - Total hours = sum of hours across all piles. Is `total_hours <= h`?

```cpp
bool canEatInTime(const vector<int>& piles, int speed, int h) {
    long long total_hours = 0;
    for (int p : piles) {
        // Integer ceiling division: (p + speed - 1) / speed
        total_hours += (p + speed - 1) / speed;
    }
    return total_hours <= h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int low = 1;
    int high = *max_element(piles.begin(), piles.end());
    int ans = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canEatInTime(piles, mid, h)) {
            ans = mid;
            high = mid - 1; // Try smaller speed
        } else {
            low = mid + 1;  // Too slow, increase speed
        }
    }
    return ans;
}
```

---

## The Two Sub-Types: Min vs Max

| Optimization Goal | Monotonic Form | When `isFeasible(mid) == true` | Output |
|:---|:---|:---|:---|
| **Minimize the Maximum** (Ship packages, Koko, Painter's partition) | `[F, F, F, T, T, T]` | Record `ans = mid`, try smaller: `high = mid - 1` | Smallest `T` |
| **Maximize the Minimum** (Aggressive cows, Magnetic balls) | `[T, T, T, F, F, F]` | Record `ans = mid`, try larger: `low = mid + 1` | Largest `T` |

---

## Traps to Avoid

> [!WARNING]
> 1. **Integer Overflow in Ceiling / Sums:** When adding hours or weights, the sum can easily exceed 32-bit `int`. Always use `long long` for accumulators inside `isFeasible()`.
> 2. **Integer Division Ceiling:** Avoid `ceil((double)a / b)` due to floating-point precision errors. Use integer math: `(a + b - 1) / b`.
> 3. **Improper Search Bounds:** Setting `low = 0` when speed cannot be 0 results in division by zero (`mid = 0`). Verify boundary physics!

---

## How to Recognize Binary Search on Answers in an Interview

Look for these dead giveaways in the problem statement:
1. *"Find the minimum ... such that all items are completed within K units."*
2. *"Maximize the minimum distance / allocation..."*
3. *"Minimize the maximum sum across K partitions..."*
4. The array itself does **not** need to be sorted; only the monotonic property of the answer space matters!
