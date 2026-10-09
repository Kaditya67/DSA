# String Patterns: Quick Reference & Cheatsheet

A practical cheatsheet for string algorithmic patterns. Use this page to diagnose whether a problem is a symmetric scan or a dynamic window, and avoid the common traps.

---

## 1. How to Pick Your Pattern

Ask yourself these diagnostic questions:

1. **Is the problem about symmetry or reversal?**
   - Palindrome check, symmetric comparison, or longest palindromic substring $\to$ **Two-Pointer (Palindrome)**
2. **Is it asking about contiguous substrings with character constraints?**
   - Longest substring without duplicates, at most `K` distinct characters, anagram match, or minimum window containing pattern $\to$ **Sliding Window (String)**
3. **Is it asking for "Exactly K" distinct characters?**
   - Use the reduction trick: `Exactly(K) = AtMost(K) - AtMost(K - 1)`.

---

## 2. Comparison Matrix

| Pattern | Input Signal | When to Use | Time | Space |
|:---|:---|:---|:---:|:---:|
| **[01. Two-Pointer (Palindrome)](./01-two-pointer-palindrome/README.md)** | Symmetry, palindrome, inward/outward expansion | Valid Palindrome I & II, Longest Palindromic Substring | `O(N)` to `O(N^2)` | `O(1)` |
| **[02. Sliding Window (String)](./02-sliding-window-string/README.md)** | Contiguous substring, character frequency limits | Longest substring without repeat, Min Window Substring, Find All Anagrams | `O(N)` | `O(1)` (size 128 / 26) |

---

## 3. Visual Decision Tree

```text
Problem asks for an answer over a string:
│
├── Symmetry, palindrome, or centered expansion?
│   └── 01. Two-Pointer (Palindrome)
│       ├── Inward: left -> <- right (Valid Palindrome I & II)
│       └── Outward: expand around 2N - 1 centers (Longest Palindromic Substring)
│
└── Substrings, character frequency, or window constraints?
    └── 02. Sliding Window (String)
        ├── Longest valid: expand right, shrink left on invalidity
        ├── Shortest valid: expand right until complete, shrink left to minimize
        └── Exactly K: AtMost(K) - AtMost(K - 1)
```

---

## 4. Code Blueprints

### Two-Pointer (Valid Palindrome)
```cpp
int left = 0, right = s.size() - 1;
while (left < right) {
    while (left < right && !isalnum(s[left])) left++;
    while (left < right && !isalnum(s[right])) right--;
    if (tolower(s[left++]) != tolower(s[right--])) return false;
}
return true;
```

### Longest Palindromic Substring (Expand Around Center)
```cpp
int expand(const string& s, int l, int r) {
    while (l >= 0 && r < s.size() && s[l] == s[r]) { l--; r++; }
    return r - l - 1;
}
// In main loop: check both odd expand(s, i, i) and even expand(s, i, i + 1)
```

### Longest Substring Without Repeating Characters
```cpp
vector<int> last_pos(128, -1);
int left = 0, max_len = 0;
for (int right = 0; right < s.size(); right++) {
    if (last_pos[s[right]] >= left) {
        left = last_pos[s[right]] + 1;
    }
    last_pos[s[right]] = right;
    max_len = max(max_len, right - left + 1);
}
```

---

## 5. Quick Traps Checklist

Before you write string solutions, verify these:

- [ ] **Are there both odd and even palindrome centers?**  
  Remember that `"aba"` has a single character center `'b'`, while `"abba"` has a center between two `'b'`s.
- [ ] **Did you verify `last_pos[c] >= left` before jumping?**  
  If the character was seen *before* the current window, do not jump `left` backward.
- [ ] **Are you allocating unnecessary HashMaps?**  
  For ASCII strings, `vector<int> freq(128, 0)` is cache-friendly and runs in strict `O(1)` space.
- [ ] **Did you handle case-insensitivity and non-alphanumeric characters?**  
  Use `isalnum()` and `tolower()` when problem specifies alphanumeric palindrome rules.
- [ ] **Is `s.size() < t.size()` handled early?**  
  For anagram/minimum window matching, return empty immediately when string length is less than target.

