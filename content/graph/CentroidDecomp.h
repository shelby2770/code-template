/**
 * Author: Arman Ferdous
 * Date: 2025-06-20
 * License: CC0
 * Source: Online
 * Description: Divide and conquer on trees. Useful for solving problems regarding all pairs of paths. 
 * Simple modifications are needed to integrate TreeBinarize into this.
 * Usage: Just call decompose(1). ctp[u] = parent of u in ctree. cth[u] = height of u in ctree, 
 * root has height = 1. dist[u][h] = original tree distance (u -> ctree ancestor of u at height h).
 * Time: O(N \lg N)
 * Status: tested
 */
// H = __lg(N), reset: cth, ctp, dist
int sub[N], cth[N], ctp[N], dist[N][H + 1];
void dfs_siz (int u, int f) {
  sub[u] = 1;
  for (int v : g[u]) if (!cth[v] && v ^ f) 
    dfs_siz(v, u), sub[u] += sub[v];
}
int fc (int u, int f, int lim) {
  for (int v : g[u]) if (!cth[v] && v ^ f && sub[v] > lim) return fc(v, u, lim);
  return u;
}
void dfs_dist (int u, int f, int d, int h) {
  dist[u][h] = d;
  for (int v : g[u]) if (!cth[v] && v ^ f) 
    dfs_dist(v, u, d + 1, h);
}
void decompose (int u, int f = 0, int h = 1) {
  dfs_siz(u, 0);
  u = fc(u, 0, sub[u] >> 1);
  dfs_dist(u, 0, 0, h);
  cth[u] = h, ctp[u] = f; // u now deleted
  for (int v : g[u]) if (!cth[v]) 
    decompose(v, u, h + 1);
}
