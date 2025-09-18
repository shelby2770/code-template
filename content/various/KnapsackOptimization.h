/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Optimized Knapsack with Square Root Decomposition.
 * For knapsack with n items and total weight sum ≤ n, uses sqrt decomposition
 * to reduce time complexity from O(n²) to O(n√n).
 * Time: O(n√n)
 * Status: Theoretical
 */
#pragma once

/*
But actually we can do better. For the knapsack problem, it has at most $n$ items, and the
sum of weights of all items is also at most $n$. We can do a sqrt decomposition trick here.

\begin{itemize}
  \item For items with weight $\geq \sqrt{n}$, there are at most $\sqrt{n}$ such items.
  \item For items with weight $< \sqrt{n}$, we count the number of items for each different weight.
  If there are $c_w$ items for weight $w$, we decompose $c_w$ into
  \[
     c_w = 2^0 + 2^1 + \dots + 2^k + y
  \]
  where $k$ is the largest integer satisfying $2^0 + 2^1 + \dots + 2^k \leq c_w$.
  Then we create new items with weights
  \[
     2^0 \cdot w,\; 2^1 \cdot w,\; \dots,\; 2^k \cdot w,\; y \cdot w.
  \]
  The set of new items is the same as $c_w$ items with weight $w$ if we only consider the
  different sum of weights the set of items can achieve. Now we only have
  \[
     \sum_{w=1}^{\sqrt{n}} \log(c_w) = \sqrt{n} \text{ items.}
  \]
\end{itemize}

The total time complexity is
\[
   O(\sqrt{n} \cdot n + \sqrt{n} \cdot n) = O(n \sqrt{n}).
\]
*/
