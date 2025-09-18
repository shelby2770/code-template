/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Merge Sort Tree for range queries counting elements smaller/greater than k.
 * Find the number of elements smaller and greater than k in a given range $[l,r]$.
 * In case of updates, use ordered\_multiset instead of vector.
 * Time: Build: $O(N \log N)$, Query: $O(\log^2 N)$
 * Usage: build(1, 1, n); query(1, 1, n, l, r, k);
 */
#pragma once

vector<int> t[N << 2];

vector<int> merge(const vector<int> &a, const vector<int> &b) {
  vector<int> ret;
  int i = 0, j = 0;
  while (i < (int)a.size() && j < (int)b.size()) {
    if (a[i] < b[j]) ret.push_back(a[i++]);
    else ret.push_back(b[j++]);
  }
  while (i < (int)a.size()) ret.push_back(a[i++]);
  while (j < (int)b.size()) ret.push_back(b[j++]);
  return ret;
}

vector<int> build(int node, int b, int e) {
  if (b == e) return t[node] = { a[b] };
  int m = (b + e) >> 1;
  return t[node] = merge(build(node << 1, b, m), build((node << 1) | 1, m + 1, e));
}

pii query(int node, int b, int e, int l, int r, int k) {
  if (b > r || e < l) return {0, 0};
  if (b >= l && e <= r) {
    int smaller = lower_bound(t[node].begin(), t[node].end(), k) - t[node].begin();
    int greater = (int)t[node].size() - (upper_bound(t[node].begin(), t[node].end(), k) - t[node].begin());
    return {smaller, greater};
  }
  int m = (b + e) >> 1;
  auto q1 = query(node << 1, b, m, l, r, k);
  auto q2 = query((node << 1) | 1, m + 1, e, l, r, k);
  return {q1.first + q2.first, q1.second + q2.second};
}
