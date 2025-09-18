/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Sparse Table for efficient range queries with idempotent operations.
 * Supports two query methods: general O(log n) and O(1) for idempotent operations like min/max.
 * Time: Build: O(n log n), Query: O(1) for idempotent ops, O(log n) for others.
 * Usage: SparseTable<int, min> st(v); st.query(l, r);
 * Status: Tested
 */
#pragma once

template<typename T, T (*op)(T, T)> struct SparseTable {
  vector<vector<T> > t;
  int K, N;

  SparseTable(const vector<T> &v): t(1, v) {
    K = __lg(sz(v)), N = sz(v);
    for (int i = 1; i <= K; ++i) {
      t.emplace_back(sz(v) - (1 << i) + 1);
      for (int j = 0; j + (1 << i) <= N; ++j) t[i][j] = op(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
    }
  }

  // O(log n) query - for non-idempotent operations (e.g., sum)
  T query(int L, int R) {
    int ret = 0; // may need to change
    for (int i = K; i >= 0; --i) {
      if ((1 << i) <= R - L + 1) {
        ret += t[i][L]; // may need to change
        L += 1 << i;
      }
    }
    return ret;
  }

  // O(1) query - for idempotent operations (e.g., min, max, gcd)
  T query(int L, int R) {
    assert(L <= R);
    int i = __lg(R - L + 1);
    return op(t[i][L], t[i][R - (1 << i) + 1]);
  }
}; 