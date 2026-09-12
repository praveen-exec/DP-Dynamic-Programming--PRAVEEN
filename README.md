# DP-Dynamic-Programming-PRAVEEN
# Problem 1
# Subset Sum Problem

This repository contains the solution to the **Subset Sum Problem** using three different approaches:

1. Recursion
2. Dynamic Programming – Memoization (Top-Down)
3. Dynamic Programming – Bottom-Up (Tabulation)

---

## Problem Statement

Given an array of integers and a target sum, determine whether there exists a **subset** of the array whose elements add up exactly to the given target sum.

### Example

```text
Array = {1, 2, 3, 4}
Target Sum = 5
```

Possible subsets are:

```text
{1, 4} = 5
{2, 3} = 5
```

Therefore, the answer is:

```text
Yes
```

---

## Approaches

### 1. Recursion

The recursive solution considers two choices for every element:

* **Exclude** the current element
* **Include** the current element

```text
                    Element
                   /       \
              Exclude     Include
                 |            |
             n-1, sum    n-1, sum-element
```

### Base Cases

```cpp
if(sum == 0)
    return true;
```

If the target sum becomes `0`, a valid subset has been found.

```cpp
if(n == 0)
    return false;
```

If there are no elements left and the sum is still not `0`, the subset cannot be formed.

### Complexity

* Time: **O(2^n)**
* Space: **O(n)** recursion stack

---

## 2. Memoization (Top-Down DP)

The recursive solution repeatedly solves the same subproblems.

To avoid recalculating them, we store the result in a 2D DP table.

```cpp
dp[n][sum]
```

represents:

> Whether `sum` can be formed using the first `n` elements.

Initially:

```cpp
dp.resize(n + 1, vector<int>(sum + 1, -1));
```

Here:

* `-1` → State has not been calculated
* `0` → False
* `1` → True

### Recurrence

If the current element is greater than the required sum:

```cpp
if(set[n-1] > sum)
    return dp[n][sum] = isSOS(set, sum, n-1, dp);
```

We cannot include the element, so we **must exclude it**.

Otherwise, we have two choices:

```cpp
dp[n][sum] =
    isSOS(set, sum, n-1, dp) ||
    isSOS(set, sum-set[n-1], n-1, dp);
```

That means:

```text
Exclude current element
        OR
Include current element
```

### Complexity

* Time: **O(n × sum)**
* Space: **O(n × sum)**

---

## 3. Bottom-Up DP (Tabulation)

Instead of using recursion, we directly build the DP table from smaller subproblems to larger subproblems.

### DP Definition

```cpp
dp[i][j]
```

means:

> Can we form sum `j` using the first `i` elements?

### Initialization

If the target sum is `0`, we can always form it by choosing an empty subset:

```cpp
dp[i][0] = true;
```

If there are `0` elements, we cannot form any positive sum:

```cpp
dp[0][j] = false;
```

### Transition

If the current element is greater than the current sum:

```cpp
if(set[i-1] > j)
    dp[i][j] = dp[i-1][j];
```

We cannot include it, so we exclude it.

Otherwise:

```cpp
dp[i][j] =
    dp[i-1][j] ||
    dp[i-1][j-set[i-1]];
```

Meaning:

```text
                    Current Element
                    /              \
               Exclude            Include
                  |                  |
             dp[i-1][j]     dp[i-1][j-element]
```

### Complexity

* Time: **O(n × sum)**
* Space: **O(n × sum)**

---

## Comparison

| Approach    | Time Complexity | Space Complexity | Technique   |
| ----------- | --------------: | ---------------: | ----------- |
| Recursion   |          O(2^n) |             O(n) | Recursive   |
| Memoization |      O(n × sum) |       O(n × sum) | Top-Down DP |
| Bottom-Up   |      O(n × sum) |       O(n × sum) | Tabulation  |

---

## Example

For:

```text
Array = {1, 2, 3, 4}
Target = 5
```

We can form the target using:

```text
1 + 4 = 5
```

or

```text
2 + 3 = 5
```

Output:

```text
Sum of Subsets Possible or Not ?
Yes!
```

---

## Key Concept

The main idea of the Subset Sum problem is:

> **For every element, either Take it or Don't Take it.**

The recursive relation is:

```cpp
Exclude OR Include
```

which becomes:

```cpp
dp[i][j] = dp[i-1][j] ||
           dp[i-1][j-set[i-1]];
```

---

## Learning Progression

This problem demonstrates the progression of Dynamic Programming:

```text
Recursion
    ↓
Overlapping Subproblems
    ↓
Memoization
    ↓
Bottom-Up DP
```

### Recursion

Solve every subproblem independently.

### Memoization

Store already calculated subproblems.

### Bottom-Up

Start from the smallest subproblems and build the final answer iteratively.

---

## Files

```text
01_Recursion.cpp
02_Memoization.cpp
03_BottomUp.cpp
README.md
```

---

## Conclusion

The Subset Sum problem is a classic example of **0/1 decision-based Dynamic Programming**.

Each element can be selected **at most once**, and for every element we decide:

```text
Take
  OR
Don't Take
```

The Bottom-Up DP approach improves the exponential recursive solution from:

```text
O(2^n)
```

to:

```text
O(n × sum)
```

making it much more efficient for larger inputs.
