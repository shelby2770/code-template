/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Disjoint Set Union (DSU) implementation
 * Time: O(n) amortized
 * Status: Tested
 */
#pragma once

vector<int> parent(N), siz(N, 1);
iota(parent.begin(),parent.end(),0);
int find(int v) { return v == parent[v] ? v : parent[v] = find(parent[v]); }
void unite(int a, int b) {
  a = find(a), b = find(b);
  if (a != b) {
    if (siz[a] < siz[b]) swap(a, b);
    parent[b] = a;
    siz[a] += siz[b];
  }
} 