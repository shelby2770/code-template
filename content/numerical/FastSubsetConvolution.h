/**
 * Author: Online
 * Date: 2017-10-31
 * License: CC0
 * Source: CF Blog
 * Description: $\textnormal{ans}[i] = \sum_{j \subseteq i} f_j g_{i \oplus j}$
 * Usage: 
 * Time: O(n^2 2^n) or, O(N \log^2 N)
 */

int f[N], g[N], fh[LG][N], gh[LG][N], h[LG][N], ans[N];
void conv() {
for (int mask = 0; mask < 1 << n; ++mask) {
 fh[__builtin_popcount(mask)][mask]=f[mask];
 gh[__builtin_popcount(mask)][mask]=g[mask];
} 
for (int i = 0; i <= n; ++i) {
 for (int j = 0; j < n; ++j)
  for (int mask = 0; mask < 1 << n; ++mask)
   if (mask & 1 << j) {
    fh[i][mask] += fh[i][mask ^ 1 << j];
    gh[i][mask] += gh[i][mask ^ 1 << j];
   }
}
for (int mask = 0; mask < 1 << n; ++mask) {
 for (int i = 0; i <= n; ++i)
  for (int j = 0; j <= i; ++j)
   h[i][mask]+=fh[j][mask] * gh[i-j][mask];
}
for (int i = 0; i <= n; ++i) {
 for (int j = 0; j < n; ++j)
  for (int mask = 0; mask < 1 << n; ++mask)
   if (mask & 1 << j) 
    h[i][mask] -= h[i][mask ^ 1 << j];
}
for (int mask = 0; mask < 1 << n; ++mask) 
 ans[mask]=h[__builtin_popcount(mask)][mask];
}
