/**
 * Author: 
 * Date: 2025-06-19
 * License: 
 * Source: CLRS
 * Description: APSP on weighted directed graphs with no negative cycles. Add a dummy node $q$ connected by 0-weighted edge to each other node. Then run Bellman from $q$ to find minimum weight $h(v)$ of a path $q \rightsquigarrow v$ (terminate if negative cycle found). Next, reweight the original graph: $\forall u \rightarrow v$ with weight $w(u,v)$, assign new weight $w(u,v) + h(u) - h(v)$. Now $D(u,v) = \textnormal{Dijkstra}(u,v) + h(v) - h(u)$.
 * Time: O(Bellman) + O(V) * O(Dijkstra)
 */
