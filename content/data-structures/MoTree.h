/**
 * Author: Arman Ferdous
 * Date: 2019-12-28
 * License: CC0
 * Source: codeforces
 * Description: Build Euler tour of $2N$ size - write node at first enter and last exit. Now, $\texttt{Path}(u, v)$ with $in[u] < in[v]$ is a segment. If $\texttt{lca}(u,v) = u$ then it is $[in[u], in[v]]$. Otherwise it is $[out[u], in[v]] + \texttt{LCA node}.$ Nodes that appear exactly once in each segment are relevant, ignore others, handle LCA separately.
 * Time: $O(Q \sqrt N)$
 */

