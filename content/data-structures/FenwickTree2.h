/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: 1-indexed Fenwick Tree with range query and range update capabilities.
 * \texttt{query(i): sum in [1, i];}\\
 * \texttt{query(l, r): sum in [l, r];}\\
 * \texttt{upd(i, val): a[i] += val;}\\
 * \texttt{upd(l, r, val): a[l..r] += val;}
 * Time: All operations are $O(\log N)$.
 */
#pragma once

template<class T> struct BIT { //1-indexed
  int n;
  vector<T> t;
  BIT() {
  }
  BIT(int _n) {
    n = _n;
    t.assign(n + 1, 0);
  }
  T query(int i) {
    T ans = 0;
    for (; i >= 1; i -= (i & -i)) ans += t[i];
    return ans;
  }
  void upd(int i, T val) {
    if (i <= 0) return;
    for (; i <= n; i += (i & -i)) t[i] += val;
  }
  void upd(int l, int r, T val) {
    upd(l, val);
    upd(r + 1, -val);
  }
  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
}; 