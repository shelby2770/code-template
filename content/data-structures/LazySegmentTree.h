/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Simple Lazy Segment Tree with range updates and range queries.
 * Supports both range sum updates and range assignment updates (commented options).
 * Modify merge function and identity elements based on the problem.
 * Time: Build: $O(N)$, Update: $O(\log N)$, Query: $O(\log N)$
 * Usage: ST st(n); st.upd(l, r, val); st.query(l, r);
 * Status: Tested
 */
#pragma once

// modify as needed
int merge(int a, int b) { return a + b; }

struct ST {
  int n;
  vector<int> t, lazy;
  const int LAZY_DEFAULT = -1; // may need to change
  const int IDENTITY = 0; // may need to change

  ST(int _n) {
    n = _n;
    t.assign(4 * n, IDENTITY);
    lazy.assign(4 * n, LAZY_DEFAULT);
  }

  void push(int node, int b, int e) {
    if (lazy[node] == LAZY_DEFAULT) return;
    t[node] += (e - b + 1) * lazy[node];
    // t[node] = (e - b + 1) * lazy[node];
    if (b != e) {
      lazy[node << 1] += lazy[node];
      lazy[(node << 1) | 1] += lazy[node];
      // lazy[node << 1] = lazy[(node << 1) | 1] = lazy[node];
    }
    lazy[node] = LAZY_DEFAULT;
  }

  void upd(int node, int b, int e, int l, int r, int v) {
    push(node, b, e);
    if (b > r || e < l) return;
    if (b >= l && e <= r) {
      lazy[node] += v;
      // lazy[node] = v;
      push(node, b, e);
      return;
    }
    int m = (b + e) >> 1;
    upd(node << 1, b, m, l, r, v);
    upd((node << 1) | 1, m + 1, e, l, r, v);
    t[node] = merge(t[node << 1], t[(node << 1) | 1]);
  }

  int query(int node, int b, int e, int l, int r) {
    push(node, b, e);
    if (b > r || e < l) return IDENTITY; // Identity element
    if (b >= l && e <= r) return t[node];
    int m = (b + e) >> 1;
    return merge(query(node << 1, b, m, l, r), query((node << 1) | 1, m + 1, e, l, r));
  }

  void upd(int l, int r, int val) { upd(1, 1, n, l, r, val); }
  int query(int l, int r) { return query(1, 1, n, l, r); }
};
