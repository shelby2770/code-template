/**
 * Author: Arman Ferdous
 * Date: 2025-06-20
 * License: CC0
 * Source: Online
 * Description: Given a weighted tree in edge-listing representation, transforms it into a binary tree by adding at most $2n$ extra nodes. 
 * Usage: call add_edge() for both directions to create the tree. Then call binarize(1). Will change n.
 * Status: stress-tested
 */

// N = 3 * max nodes, M = 2 * N
int n, o = 2;
int to[M],wgt[M],prv[M],nxt[M],lst[N],deg[N];

void add_edge (int u, int v, int w) {
  to[o] = v, wgt[o] = w, deg[v]++;
  prv[o] = lst[u], lst[u] = nxt[lst[u]] = o++;
}
void binarize (int u, int f = 0) {
  int d = deg[u] - 2 - (f != 0);
  if (d > 0) {
    int tmp_lst = (to[lst[u]] == f ? prv[lst[u]] : lst[u]), x;
    for (int e = lst[u], at = n+d; at > n; ){
        x = prv[e];
        if (to[e] == f) { e = x; continue; }
        nxt[x] = nxt[e];
        nxt[e] ? prv[nxt[e]] = x : lst[u] = x;
        prv[e] = lst[at], nxt[e] = 0;
        lst[at] = nxt[lst[at]] = e, deg[at]++;
        to[e ^ 1] = at;
        if (e != tmp_lst) --at;
        e = x;
    }
    for (int i=1, p=u; i <= d; p = n + i++)
       add_edge(p, n + i, 0), 
       add_edge(n + i, p, 0);
    n += d, deg[u] -= d + 1;
  }
  for (int e = lst[u]; e; e = prv[e]) 
    if (to[e] != f) binarize(to[e], u);
}
