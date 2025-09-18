/**
 * Author: adamant
 * Source: https://codeforces.com/blog/entry/53170
 * Description: Subtree of v: $[in_v, out_v)$. Path from $v$ to the last vertex in ascending heavy path from $v$ (which is $nxt_v$) will be in $[in_{nxt_v}, in_v]$.
 * Usage: each g[u] must not contain the parent. call dfs_sz(), then dfs_hld(). Be careful about switching to 1-indexing. 
 * Status: 
 */

void dfs_sz(int u = 0) { sz[u] = 1;
  for(auto &v: g[u]) {
    dfs_sz(v); sz[u] += sz[v];
    if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
  }
}
void dfs_hld(int u = 0) { in[u] = t++;
  for(auto v: g[u]) {
    nxt[v] = (v == g[u][0] ? nxt[u] : v);
    dfs_hld(v);
  } out[u] = t;
}
