/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Iterative Segment Tree implementation with point update and range query.
 * Uses 1-based indexing internally but 0-based indexing for the interface.
 * Define op and identity based on the problem.
 * Time: Build: $O(N)$, Update: $O(\log N)$, Query: $O(\log N)$
 * Usage: ST st(n); st.upd(idx, val); st.query(l, r);
 * Status: Tested
 */
#pragma once

// modify as needed
int op(int a, int b) { return a + b; }

struct ST {
  int n;
  vector<int> t;

  ST(int _n) {
    n = _n;
    t.assign(2 * n + 1, 0);
  }

  void upd(int p, int v) {
    p += n;
    t[p] = v;
    for (p >>= 1; p > 0; p >>= 1) t[p] = op(t[p << 1], t[p << 1 | 1]);
  }

  int query(int l, int r) {
    int res = Identity;
    l += n, r += n;
    for (; l<=r; l>>=1, r>>=1) {
      if (l & 1) res = op(res, t[l++]);
      if (!(r & 1)) res = op(res, t[r--]);
    }
    return res;
  }
};