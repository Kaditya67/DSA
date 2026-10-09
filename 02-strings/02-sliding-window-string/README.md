# Sliding Window (Strings) Pattern

## Why Brute Force Fails First?

Substring problems typically ask:
- *"What is the length of the longest substring without repeating characters?"*
- *"What is the minimum substring containing all characters of pattern T?"*

The naive way:
- Check all `O(N^2)` substrings.
- For each substring, count frequencies of characters in `O(N)` or `O(26)` time.
- Total time: `O(N^3)` or `O(N^2)`.

> [!CAUTION]
> If `N = 10^5`, an `O(N^2)` check requires `10^{10}` operations $\to$ **Time Limit Exceeded (TLE)**!

With Sliding Window, both `left` and `right` traverse the string at most once. Each character is visited twice $\to$ strictly **O(N)** time with **O(1)** or **O(K)** auxiliary space (where `K` is the alphabet size, at most 128 for ASCII or 26 for lowercase).

---

## What Enables This Technique?

Substrings are **contiguous** slices of a string.  
Because character sets are finite (e.g., 26 lowercase English letters or 128 ASCII symbols), we can track the frequency of characters inside the window using a fixed-size frequency array or hash map in `O(1)` memory.

---

## The Two Core Variants

### 1. Longest Substring Satisfying a Condition (Expand & Contract)

**Goal:** Find the maximum length of a substring satisfying a property (e.g., *no duplicate characters*, or *at most K distinct characters*).

#### Strategy
- Expand `right` and update the frequency map.
- If the window becomes **invalid** (e.g., character count > 1), shrink `left` until the window is valid again.
- Record the maximum window length: `right - left + 1`.

#### Skeleton: Longest Substring Without Repeating Characters
```cpp
int lengthOfLongestSubstring(string s) {
    vector<int> freq(128, 0); // ASCII character tracker
    int left = 0, max_len = 0;

    for (int right = 0; right < s.size(); right++) {
        freq[s[right]]++;

        // While duplicate exists, shrink window from left
        while (freq[s[right]] > 1) {
            freq[s[left]]--;
            left++;
        }

        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}
```

#### Optimization with Last Seen Index
Instead of moving `left` one step at a time, store the **last seen index** of each character. When a duplicate is encountered, jump `left` directly past the previous occurrence:
```cpp
int lengthOfLongestSubstringOptimized(string s) {
    vector<int> last_pos(128, -1);
    int left = 0, max_len = 0;

    for (int right = 0; right < s.size(); right++) {
        // If s[right] was seen inside current window, jump left past it
        if (last_pos[s[right]] >= left) {
            left = last_pos[s[right]] + 1;
        }
        last_pos[s[right]] = right;
        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}
```

---

### 2. Minimum Window Substring (Exact Match / Subset Match)

**Goal:** Find the shortest substring in `S` that contains all characters of pattern `T`.

#### Strategy
1. Build a target frequency map for string `T`. Track how many unique characters still need their target counts satisfied (`required_matches`).
2. Expand `right`:
   - Decrement the needed count for `s[right]`.
   - When a character's needed count reaches `0`, decrement `required_matches`.
3. When `required_matches == 0` (window is valid):
   - Record the current window length as a candidate minimum.
   - Shrink `left` to find smaller valid windows until the window becomes invalid again.

#### Basic Skeleton
```cpp
string minWindow(string s, string t) {
    vector<int> target_freq(128, 0);
    for (char c : t) target_freq[c]++;

    int required = 0;
    for (int count : target_freq) {
        if (count > 0) required++;
    }

    vector<int> window_freq(128, 0);
    int left = 0, formed = 0;
    int min_len = INT_MAX, start_idx = 0;

    for (int right = 0; right < s.size(); right++) {
        char c = s[right];
        window_freq[c]++;

        if (target_freq[c] > 0 && window_freq[c] == target_freq[c]) {
            formed++;
        }

        // While window contains all required characters, shrink left
        while (formed == required) {
            if (right - left + 1 < min_len) {
                min_len = right - left + 1;
                start_idx = left;
            }

            char left_char = s[left];
            window_freq[left_char]--;
            if (target_freq[left_char] > 0 && window_freq[left_char] < target_freq[left_char]) {
                formed--;
            }
            left++;
        }
    }

    return min_len == INT_MAX ? "" : s.substr(start_idx, min_len);
}
```

---

### 3. The "Exactly K" Substring Reduction Trick

Problems asking for substrings with **exactly K** distinct characters are notoriously tricky because contracting `left` can break both lower and upper bounds at the same time.

> [!IMPORTANT]
> **The Reduction Formula:**  
> `Exactly(K) = AtMost(K) - AtMost(K - 1)`  
>
> Writing a helper function for `atMost(K)` is standard sliding window:  
> - Expand `right`, track distinct characters.  
> - Shrink `left` while distinct characters > `K`.  
> - Add `(right - left + 1)` valid substrings ending at `right`.  
> Compute `atMost(K) - atMost(K - 1)` to get the exact count.

---

## Traps to Avoid

> [!WARNING]
> 1. **Alphabet Size Space:** Don't allocate a `hash_map<char, int>` when an array `vector<int> freq(128, 0)` or `vector<int> freq(26, 0)` is faster and uses strictly `O(1)` memory.
> 2. **Empty / Impossible Inputs:** When `s.size() < t.size()`, immediately return `""`.
> 3. **Off-by-One in Jumps:** When jumping `left` with `last_pos[char] + 1`, ensure the previous occurrence was **inside** the current window: `last_pos[char] >= left`. Otherwise, you could accidentally move `left` backward!

---

## How to Recognize String Sliding Window in an Interview

1. **Keywords:** "Longest substring...", "Smallest substring containing...", "Substring with at most K distinct...", "Permutation in string / Anagrams".
2. **Contiguous constraint:** Must be a contiguous substring (not subsequence).
3. **Fixed alphabet:** Works exceptionally well because characters are bounded by ASCII (128) or lowercase English (26).
