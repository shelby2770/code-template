/**
 * Author: Online
 * Date: 2025-06-17
 * License: CC0
 * Source: Online
 * Description: Range add Range sum with FT.
 * Time: Both operations are $O(\log N)$.
 * Status: solved SPOJ HORRIBLE
 */

FT f1(n), f2(n);
// a[l...r] += v; 0 <= l <= r < n
auto upd = [&](int l, int r, ll v) {
  f1.update(l, v), f1.update(r + 1, -v);
  f2.update(l, v*(l-1)), f2.update(r+1, -v*r);
}; // a[l] + ... + a[r]; 0 <= l <= r < n
auto sum = [&](int l, int r) { ++r;
  ll sub = f1.query(l) * (l-1) - f2.query(l);
  ll add = f1.query(r) * (r-1) - f2.query(r);
  return add - sub;
};
