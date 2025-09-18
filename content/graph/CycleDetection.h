/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Cycle detection for directed and undirected graphs
 * Time: O(V+E)
 */
#pragma once

//cycle detect (undirected)
bool dfs(int u, int p) {
  vis[u] = true;
  par[u] = p;
  for (auto &it: adj[u]) {
    if (it == p) continue;
    if (vis[it]) {
      s = it, e = u;
      return true;
    }
    if (dfs(it, u)) return true;
  }
  return false;
};

//cycle detect (directed)
bool dfs(int v) {
  color[v] = 1;
  for (int u : adj[v]) {
    if (color[u] == 0) {
      parent[u] = v;
      if (dfs(u))
        return true;
    } else if (color[u] == 1) {
      cycle_end = v;
      cycle_start = u;
      return true;
    }
  }
  color[v] = 2;
  return false;
} 