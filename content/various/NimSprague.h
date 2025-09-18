/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Nim and Sprague-Grundy Theory for impartial combinatorial games.
 * Essential theory, definitions, theorems, and algorithmic template for computing Grundy numbers.
 * Time: O(N + E) for DAG, O(N + E + mex costs) in general
 * Usage: Compute Grundy numbers for game positions, XOR for disjoint sums
 */
#pragma once

/*
% Nim and Sprague-Grundy Theory

Basic Definitions:
- Impartial game: Two-player turn-based, no chance, legal moves depend only on position
- Normal play: Player who cannot move loses
- Terminal position: No legal moves available
- mex(S) = minimum excluded value = min{n in N: n not in S}

Nim Game (Bouton's Theorem):
A Nim position (h1, h2, ..., hk) is losing for current player iff
h1 XOR h2 XOR ... XOR hk = 0 (where XOR is bitwise exclusive or)

Grundy Number Definition:
g(x) = mex{g(y) : y in Options(x)}
Terminal positions have g(x) = 0

Sprague-Grundy Theorem:
For disjoint sum of games G1 + G2 + ... + Gm:
g(G) = g(G1) XOR g(G2) XOR ... XOR g(Gm)
Sum is losing position iff XOR of component nimbers = 0

Algorithmic Template:
*/

int mex(const vector<int>& vals) {
  int n = vals.size();
  unordered_set<int> s(vals.begin(), vals.end());
  int m = 0;
  while (s.count(m)) ++m;
  return m;
}

vector<int> grundy;
vector<vector<int>> moves;

int compute(int u) {
  if (grundy[u] != -1) return grundy[u];
  vector<int> nxt;
  for (int v : moves[u]) nxt.push_back(compute(v));
  return grundy[u] = mex(nxt);
}

/*
Usage:
1. Build moves graph
2. Initialize: grundy.assign(N, -1)
3. Compute: for each u, call compute(u)
4. For disjoint sum: XOR the grundy values of components

Common Patterns:
- Subtraction game: g(n) = mex{g(n-s) : s in S, s <= n}
- Many games have ultimately periodic Grundy sequences
- For small nimbers (<64), use bitmask for fast mex computation

Complexity: O(N + E) plus mex costs
*/
