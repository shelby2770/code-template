/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Easy Segment Tree with point update and range query.
 * Provides merge (combine results), build (construct tree),
 * upd (point update), query (range query).
 * May need to change merge function and identity elements based on problem.
 * Time: Build: $O(N)$, Update: $O(\log N)$, Query: $O(\log N)$
 * Usage: int t[4*N]; build(1, 1, n, arr); upd(1, 1, n, idx, val); query(1, 1, n, l, r);
 * Status: Tested
 */
#pragma once

// Global array to store segment tree
int t[N << 2];

// modify as needed
int merge(int a, int b) { return a + b; }

int build(int node, int b, int e, vector<int> &v) {
  if (b == e) return t[node] = v[b];
  int m = (b + e) >> 1;
  return t[node] = merge(build(node << 1, b, m, v), build(node << 1 | 1, m + 1, e, v));
}

void upd(int node, int b, int e, int i, int v) {
  if (b == e) return void(t[node] = v);
  int m = (b + e) >> 1;
  i <= m ? upd(node << 1, b, m, i, v) : upd(node << 1 | 1, m + 1, e, i, v);
  t[node] = merge(t[node << 1], t[node << 1 | 1]);
}

int query(int node, int b, int e, int l, int r) {
  if (b > r || e < l) return 0; // Identity element - modify as needed
  if (b >= l && e <= r) return t[node];
  int m = (b + e) >> 1;
  return merge(query(node << 1, b, m, l, r), query(node << 1 | 1, m + 1, e, l, r));
}
