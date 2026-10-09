# Two-Pointer (Palindrome & Symmetry) Pattern

## Why Brute Force Fails First?

When checking if a string is a palindrome or finding the longest palindromic substring:
- The naive approach for longest palindromic substring checks every single substring `(i, j)` and tests if it reads forwards and backwards identically.
- There are `O(N^2)` substrings, and checking each takes `O(N)` time.
- Total runtime: **O(N^3)**.

> [!CAUTION]
> For `N = 1000`, `N^3 = 10^9` operations—which hits **Time Limit Exceeded (TLE)** on any modern judge.

Two-Pointer cuts palindrome validation to **O(N)** and substring expansion to **O(N^2)** with **O(1)** auxiliary space.  
How? Let's break it down.

---

## What Enables This Technique?

A palindrome has a strict geometric symmetry:
`s[i] == s[n - 1 - i]` for all valid indices.

This allows two navigation strategies:
1. **Inward Convergence:** Start at opposite ends (`left = 0`, `right = n - 1`) and step inward to verify if a sequence is mirrored.
2. **Outward Expansion:** Pick a center character (or center pair) and expand outward (`left--`, `right++`) as long as `s[left] == s[right]`.

---

## The Two Core Variants

### 1. Inward Convergence (Validation & Cleaning)

Place one pointer at `left = 0` and one at `right = n - 1`. Move them towards each other.

#### Mental Model
Think of two mirrors meeting in the center:
- If `s[left] != s[right]`, symmetry is broken immediately $\to$ return `false`.
- If equal, step inward: `left++`, `right--`.
- If non-alphanumeric characters or spaces must be ignored, skip them before comparing.

#### Basic Skeleton (Valid Palindrome with Ignored Characters)
```cpp
bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;

        // Compare case-insensitively
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}
```

#### The "At Most One Deletion" Twist (Valid Palindrome II)
What if you are allowed to delete at most one character to make it a palindrome?
- Move inward normally until you find the first mismatch: `s[left] != s[right]`.
- You only have two choices:
  1. Skip `s[left]` and check if substring `s[left + 1 ... right]` is a palindrome.
  2. Skip `s[right]` and check if substring `s[left ... right - 1]` is a palindrome.
- If either works, return `true`; otherwise `false`.

```cpp
bool isPalindromeRange(const string& s, int l, int r) {
    while (l < r) {
        if (s[l++] != s[r--]) return false;
    }
    return true;
}

bool validPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return isPalindromeRange(s, left + 1, right) || 
                   isPalindromeRange(s, left, right - 1);
        }
        left++;
        right--;
    }
    return true;
}
```

---

### 2. Outward Expansion (Expand Around Center)

Used to find palindromes inside a string (e.g., Longest Palindromic Substring).

#### The Problem with Centers
A palindrome can be centered in two ways:
1. **Odd length:** Centered at a single character (e.g., `"aba"`, center = `'b'`).
2. **Even length:** Centered between two identical characters (e.g., `"abba"`, center = `'b', 'b'`).

For a string of length `N`, there are exactly `2N - 1` possible centers (`N` single characters + `N - 1` adjacent pairs).

#### Basic Skeleton (Longest Palindromic Substring)
```cpp
int expandAroundCenter(const string& s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    // Length of the valid palindrome before mismatch:
    return right - left - 1;
}

string longestPalindrome(string s) {
    if (s.empty()) return "";
    int start = 0, max_len = 0;

    for (int i = 0; i < s.size(); i++) {
        int len1 = expandAroundCenter(s, i, i);     // Odd center
        int len2 = expandAroundCenter(s, i, i + 1); // Even center
        int len = max(len1, len2);

        if (len > max_len) {
            max_len = len;
            start = i - (len - 1) / 2;
        }
    }

    return s.substr(start, max_len);
}
```

---

## Traps to Avoid

> [!WARNING]
> 1. **Even vs Odd Centers:** Always check both `(i, i)` and `(i, i + 1)`. Forgetting even-length centers will miss cases like `"abba"`.
> 2. **Boundary Checks During While-Skips:** When skipping spaces with `while (left < right && !isalnum(s[left])) left++`, always keep `left < right` inside the inner loop to prevent index out of bounds.
> 3. **Substr Length Calculation:** When expanding outward until mismatch, `left` and `right` end up 1 step past the boundary. The length of the valid segment is `(right - 1) - (left + 1) + 1 = right - left - 1`.

---

## How to Recognize This Pattern in an Interview

1. **Mirror / Symmetry keywords:** Palindrome, reverse string, symmetric characters.
2. **Permutations of a palindrome:** Characters can form a palindrome if at most one character has an odd frequency count (HashMap / Bitmask trick).
3. **Substring centers:** Any question asking to find or count all palindromic substrings (expand around center in `O(N^2)` time, `O(1)` space vs DP `O(N^2)` space).
