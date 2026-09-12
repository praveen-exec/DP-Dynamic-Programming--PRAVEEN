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



# Problem 2 
# Matrix Chain Multiplication (MCM)

##  Overview

**Matrix Chain Multiplication (MCM)** is a classic **Dynamic Programming** problem.

The main goal is:

> Find the minimum number of scalar multiplications required to multiply a chain of matrices.

The important thing is that **matrix multiplication is associative**, which means:

```text
(A × B) × C = A × (B × C)
```

Both expressions give the same final matrix, but the **number of scalar multiplications can be very different**.

Therefore, we need to find the **best order of multiplication** that gives the minimum cost.

---

# 📚 Problem Statement

Suppose we have matrices:

```text
A1, A2, A3, ..., An
```

We want to multiply:

```text
A1 × A2 × A3 × ... × An
```

The order of multiplication can be changed using parentheses.

Our task is to determine the parenthesization that requires the **minimum number of scalar multiplications**.

---

# Important Concept

Suppose:

```text
A = 10 × 30
B = 30 × 5
```

When multiplying:

```text
A × B
```

the resulting matrix will be:

```text
10 × 5
```

The number of scalar multiplications required is:

```text
10 × 30 × 5 = 1500
```

Therefore:

```text
Cost = rows(A) × columns(A) × columns(B)
```

---

# 🧮 Matrix Representation Using Array

Instead of storing every matrix separately, we store their dimensions in an array.

For example:

```cpp
int p[] = {10, 30, 5, 60};
```

This represents:

```text
A1 = 10 × 30
A2 = 30 × 5
A3 = 5 × 60
```

Notice:

```text
Number of matrices = size of p - 1
```

Therefore:

```text
4 - 1 = 3 matrices
```

---

# Example

Consider:

```text
p = {10, 30, 5, 60}
```

Matrices:

```text
A1 = 10 × 30
A2 = 30 × 5
A3 = 5 × 60
```

There are two possible parenthesizations.

## Option 1

```text
(A1 × A2) × A3
```

First:

```text
A1 × A2

(10 × 30) × (30 × 5)
```

Cost:

```text
10 × 30 × 5
= 1500
```

Resulting matrix:

```text
10 × 5
```

Now multiply with A3:

```text
(10 × 5) × (5 × 60)
```

Cost:

```text
10 × 5 × 60
= 3000
```

Total:

```text
1500 + 3000
= 4500
```

---

## Option 2

```text
A1 × (A2 × A3)
```

First:

```text
A2 × A3

(30 × 5) × (5 × 60)
```

Cost:

```text
30 × 5 × 60
= 9000
```

Resulting matrix:

```text
30 × 60
```

Now:

```text
A1 × (A2 × A3)

(10 × 30) × (30 × 60)
```

Cost:

```text
10 × 30 × 60
= 18000
```

Total:

```text
9000 + 18000
= 27000
```

Therefore:

```text
Minimum Cost = min(4500, 27000)

             = 4500
```

---

#  Why Dynamic Programming?

A simple recursive solution tries **every possible partition**.

For example:

```text
A1 A2 A3 A4
```

We can divide the chain at different positions:

```text
A1 | A2 A3 A4
A1 A2 | A3 A4
A1 A2 A3 | A4
```

Each side is again solved recursively.

This creates many **repeated subproblems**.

For example:

```text
MCM(1,3)
```

may be calculated multiple times.

Dynamic Programming solves this problem by storing already calculated results.

---

# Recursive Approach

## Idea

Define:

```text
MCM(i, j)
```

as:

> Minimum cost required to multiply matrices from Ai to Aj.

For every possible partition `k`:

```text
Ai ... Ak | A(k+1) ... Aj
```

we calculate:

```text
Left Cost
+
Right Cost
+
Cost of multiplying the two resulting matrices
```

Then take the minimum.

---

# 🔢 Formula

For every:

```text
k = i to j-1
```

we calculate:

```text
MCM(i,k)
+
MCM(k+1,j)
+
p[i-1] × p[k] × p[j]
```

Therefore:

```text
MCM(i,j)
=
min {
    MCM(i,k)
    + MCM(k+1,j)
    + p[i-1] × p[k] × p[j]
}
```

---

# Base Case

If:

```text
i == j
```

there is only one matrix.

A single matrix does not need multiplication.

Therefore:

```cpp
if(i == j)
    return 0;
```

---

# 💻 Recursive Code

```cpp
#include <iostream>
using namespace std;

class Solution {
public:

    int min(int a, int b) {
        return a > b ? b : a;
    }

    int MCM(int p[], int i, int j) {

        // Only one matrix
        if(i == j)
            return 0;

        int result = 1e7;

        // Try every possible partition
        for(int k = i; k < j; k++) {

            result = min(
                result,
                MCM(p, i, k)
                + MCM(p, k + 1, j)
                + p[i - 1] * p[k] * p[j]
            );
        }

        return result;
    }
};

int main() {

    int p[] = {10, 30, 5, 60};

    // Number of matrices = size of p - 1
    int n = sizeof(p) / sizeof(p[0]);

    Solution obj;

    cout << "Min Scalar Mul Needed = "
         << obj.MCM(p, 1, n - 1);

    return 0;
}
```

---

# Understanding the Recursive Code

## Step 1: Base Case

```cpp
if(i == j)
    return 0;
```

Only one matrix is present.

Example:

```text
MCM(2,2)
```

There is nothing to multiply.

So:

```text
Cost = 0
```

---

## Step 2: Initialize Answer

```cpp
int result = 1e7;
```

We need to find the minimum.

So we start with a very large value.

Then every partition tries to reduce it.

---

## Step 3: Try Every Partition

```cpp
for(int k = i; k < j; k++)
```

`k` represents where we divide the matrix chain.

For:

```text
A1 A2 A3
```

possible partitions are:

```text
A1 | A2 A3
A1 A2 | A3
```

Therefore:

```text
k = 1
k = 2
```

---

## Step 4: Solve Left Part

```cpp
MCM(p, i, k)
```

This calculates the minimum cost for the matrices on the left.

---

## Step 5: Solve Right Part

```cpp
MCM(p, k + 1, j)
```

This calculates the minimum cost for the matrices on the right.

---

## Step 6: Calculate Multiplication Cost

```cpp
p[i - 1] * p[k] * p[j]
```

This is the cost of multiplying the two resulting matrices.

---

## Step 7: Take Minimum

```cpp
result = min(result, left + right + multiplication);
```

We try every possible partition and keep the smallest cost.

---

# 🌳 Recursion Tree

For:

```text
MCM(1,3)
```

we have:

```text
                MCM(1,3)
                /       \
          k = 1           k = 2
          /                 \
     MCM(1,1)          MCM(1,2)
     MCM(2,3)          MCM(3,3)
```

Notice that:

```text
MCM(1,2)
MCM(2,3)
```

and other subproblems can occur repeatedly.

This is the reason the recursive approach becomes expensive.

---

# 2️⃣ Memoization Approach

Memoization is:

> **Top-Down Dynamic Programming**

The recursive solution remains almost the same.

The only difference is that we create a DP table.

```cpp
dp[i][j]
```

stores the answer for:

```text
MCM(i,j)
```

---
#  Main Idea

Before calculating:

```cpp
MCM(i,j)
```

check whether the answer is already stored.

```cpp
if(dp[i][j] != -1)
    return dp[i][j];
```

If it is already calculated:

```text
Return it directly.
```

If not:

```text
Calculate it
      ↓
Store it in dp[i][j]
      ↓
Return it
```

---

# DP Table

Initially:

```text
dp = -1
```

Example:

```text
      j
      1   2   3
    ----------------
i 1 | -1  -1  -1
  2 | -1  -1  -1
  3 | -1  -1  -1
```

`-1` means:

```text
This subproblem has not been calculated yet.
```

After calculation, values are stored.

For example:

```text
dp[1][3] = 4500
```

---

# 💻 Memoization Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    vector<vector<int>> dp;

    int MCM(vector<int>& p, int i, int j) {

        // Base case
        if(i == j)
            return 0;

        // Already calculated
        if(dp[i][j] != -1)
            return dp[i][j];

        int ans = 1e7;

        // Try every possible partition
        for(int k = i; k < j; k++) {

            int left = MCM(p, i, k);

            int right = MCM(p, k + 1, j);

            int cost = p[i - 1] * p[k] * p[j];

            ans = min(ans, left + right + cost);
        }

        // Store answer
        return dp[i][j] = ans;
    }

    int matrixMultiplication(vector<int>& p) {

        // Number of matrices
        int n = p.size() - 1;

        // Initialize DP table with -1
        dp.resize(n + 1, vector<int>(n + 1, -1));

        return MCM(p, 1, n);
    }
};

int main() {

    vector<int> p = {10, 30, 5, 60};

    Solution obj;

    cout << "Min Scalar Mul Needed = "
         << obj.matrixMultiplication(p);

    return 0;
}
```

---

#  Memoization Code Explanation

## DP Declaration

```cpp
vector<vector<int>> dp;
```

This creates a 2D DP table.

---

## DP Initialization

```cpp
dp.resize(n + 1, vector<int>(n + 1, -1));
```

Suppose:

```text
n = 3
```

Then approximately:

```text
4 × 4
```

table is created.

Every value is initialized to:

```text
-1
```

---

## Check Already Calculated

```cpp
if(dp[i][j] != -1)
    return dp[i][j];
```

This is the most important part of memoization.

If:

```text
dp[1][3] = 4500
```

and we need:

```text
MCM(1,3)
```

again, we simply return:

```text
4500
```

No recursive calculation is required.

---

# 💡 Easy Way to Remember MCM

Whenever you see Matrix Chain Multiplication, remember:

```text
PARTITION
   ↓
LEFT
   ↓
RIGHT
   ↓
MULTIPLICATION COST
   ↓
MINIMUM
```

The formula is:

```text
LEFT + RIGHT + COST
```

and then:

```text
MINIMUM
```

So remember:

> **"Break → Solve Left → Solve Right → Multiply → Take Minimum"**

---

# 🔥 Dry Run

For:

```text
p = {10, 30, 5, 60}
```

We call:

```cpp
MCM(p, 1, 3)
```

Because there are 3 matrices.

---

## Partition 1

```text
k = 1
```

Divide:

```text
A1 | A2 A3
```

Left:

```text
MCM(1,1) = 0
```

Right:

```text
MCM(2,3)
```

For:

```text
A2 × A3
```

cost:

```text
30 × 5 × 60
= 9000
```

Then final multiplication:

```text
10 × 30 × 60
= 18000
```

Total:

```text
0 + 9000 + 18000
= 27000
```

---

## Partition 2

```text
k = 2
```

Divide:

```text
A1 A2 | A3
```

Left:

```text
MCM(1,2)
```

Cost:

```text
10 × 30 × 5
= 1500
```

Right:

```text
MCM(3,3) = 0
```

Final multiplication:

```text
10 × 5 × 60
= 3000
```

Total:

```text
1500 + 0 + 3000
= 4500
```

---

## Final Answer

Compare:

```text
Partition 1 = 27000

Partition 2 = 4500
```

Therefore:

```text
Minimum = 4500
```

---

# ⚔️ Recursion vs Memoization

| Feature              | Recursion            | Memoization          |
| -------------------- | -------------------- | -------------------- |
| Approach             | Recursive            | Recursive + DP       |
| Stores results       | ❌ No                 | ✅ Yes                |
| Repeated subproblems | ✅ Many               | ❌ Avoided            |
| Time Complexity      | Exponential          | O(n³)                |
| Space Complexity     | O(n) recursion stack | O(n²) DP + recursion |
| Speed                | Slow for large n     | Much faster          |
| DP                   | ❌                    | ✅                    |

---

# ⏱️ Complexity Analysis

## Recursive Approach

There are many possible ways to parenthesize a matrix chain.

Therefore, the number of recursive calls grows exponentially.

```text
Time Complexity: Exponential
```

The recursion depth can reach approximately:

```text
O(n)
```

Therefore:

```text
Space Complexity: O(n)
```

---

# 🚀 Memoization Complexity

There are approximately:

```text
O(n²)
```

different states:

```text
dp[i][j]
```

For every state, we try:

```text
O(n)
```

different partition points `k`.

Therefore:

```text
O(n²) × O(n)
```

which gives:

```text
O(n³)
```

### Time Complexity

```text
O(n³)
```

### Space Complexity

DP table:

```text
O(n²)
```

Recursion stack:

```text
O(n)
```

Overall:

```text
O(n²)
```

dominates.

---

# Important Observations

### 1. Number of matrices

If:

```cpp
vector<int> p = {10, 30, 5, 60};
```

then:

```text
p.size() = 4
```

but:

```text
Number of matrices = 4 - 1 = 3
```

---

### 2. Matrix numbering starts from 1

We use:

```text
MCM(p, 1, n)
```

rather than:

```text
MCM(p, 0, n-1)
```

because the formula becomes easier:

```text
p[i-1] × p[k] × p[j]
```

---

### 3. `i == j`

Means:

```text
Only one matrix
```

Therefore:

```text
Cost = 0
```

---

### 4. `k`

`k` is the partition point.

It divides:

```text
i ... j
```

into:

```text
i ... k
```

and:

```text
k+1 ... j
```

---

### 5. Why `p[i-1]`?

Suppose:

```text
Ai = p[i-1] × p[i]
```

and the left side ends at:

```text
Ak
```

The right side starts from:

```text
A(k+1)
```

After multiplying both sides, the dimensions involved in the final multiplication are:

```text
p[i-1] × p[k] × p[j]
```

Hence:

```cpp
p[i-1] * p[k] * p[j]
```

---

#  General Template for MCM

The general recursive pattern is:

```cpp
int MCM(vector<int>& p, int i, int j) {

    if(i == j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int ans = 1e7;

    for(int k = i; k < j; k++) {

        int left = MCM(p, i, k);

        int right = MCM(p, k + 1, j);

        int cost = p[i - 1] * p[k] * p[j];

        ans = min(ans, left + right + cost);
    }

    return dp[i][j] = ans;
}
```

This pattern is useful for many **interval DP / partition DP** problems.

---

# 🏆 Final Takeaway

Matrix Chain Multiplication is a classic example of **Partition DP**.

The main strategy is:

```text
Choose a partition k
        ↓
Solve left subproblem
        ↓
Solve right subproblem
        ↓
Calculate cost of combining both
        ↓
Take minimum
        ↓
Store result using DP
```

The most important formula to remember is:

```text
MCM(i,j) =
min(
    MCM(i,k)
    + MCM(k+1,j)
    + p[i-1] × p[k] × p[j]
)
```

### Final Complexity

```text
Recursive:
Time  = Exponential
Space = O(n)

Memoization:
Time  = O(n³)
Space = O(n²)
```

### One-Line Memory Trick

> **MCM = Partition + Left + Right + Multiplication Cost + Minimum**

