/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Euler tour technique for tree queries with segment tree.
 * Time: O(n) for tour, O(log n) for queries/updates
 * Usage:
 *   euler_tour(root, -1);
 *   update(1, 1, n, tin[i], tin[i], arr[i]); // Update node i's value
 *   query(1, 1, n, tin[s], tout[s]); // Query subtree sum of node s
 */
#pragma once

vector<int> t(4 * N), lazy(4 * N, -1), g[N];
int n, q, arr[N], tin[N], tout[N], timer = 0;

void euler_tour(int u, int par) {
  tin[u] = ++timer;
  for (auto &v: g[u]) if (v != par) euler_tour(v, u);
  tout[u] = timer;
}