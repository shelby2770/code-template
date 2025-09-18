/**
 * Author: AI.Cash
 * Date:
 * License: 
 * Source: https://codeforces.com/blog/entry/22072 
 * Description: 0-based indexing, \texttt{HLDSegTree} refers to the type of the segment tree
 *              The segment tree must have update([l, r), +dx) and query([l, r)) methods.
 * Time: $O((\log N)^2)$ (not sure about this, though).
 * Status: Tested
 */

template<class T, class HLDSegTree>
class HLD {
  int n;
  V<int> par, heavy,level,root,tree_pos;
  HLDSegTree tree;
private:
  int dfs(const V<V<int>>& graph, int u);
  template<class BinOp>
  void process_path(int u, int v, BinOp op);
public:
  HLD(int n_, const V<V<int>>& graph) : n(n_), par(n), heavy(n, -1), level(n), root(n), tree_pos(n), tree(n) {
    par[0] = -1;
    level[0] = 0;
    dfs(graph, 0);
    int ii = 0;
    for(int u = 0; u < n; u++) {
      if(par[u] != -1 && heavy[par[u]] == u) continue;
      for(int v = u; v != -1; v = heavy[v]) {
        root[v] = u;
        tree_pos[v] = ii++;
      }
    }
  }
  void update(int u, int v, T val) {
    process_path(u, v, [this, val](int l, int r) { tree.update(l, r, val); });
  }
  T query(int u, int v) {
    T res = T();
    process_path(u, v, [this, &res](int l, int r) { res += tree.query(l, r); });
    return res;
  }
};
template<class T, class HLDSegTree>
int HLD<T,HLDSegTree>::dfs(const V<V<int>>& graph, int u) {
   int cc = 1, max_sub = 0;
   for(int v : graph[u]) {
      if(v == par[u]) continue;
      par[v] = u;
      level[v] = level[u] + 1;
      int sub = dfs(graph, v);
      if(sub > max_sub) {
         max_sub = sub;
         heavy[u] = v;
      }
      cc += sub;
   }
   return cc;
}
template<class T, class HLDSegTree>
template<class BinOp>
void HLD<T, HLDSegTree>::process_path(int u, int v, BinOp op) {
   for(; root[u] != root[v]; v = par[root[v]]) {
      if(level[root[u]] > level[root[v]]) swap(u, v);
      op(tree_pos[root[v]], tree_pos[v]);
      assert(v != -1);
   }
   if(level[u] > level[v]) swap(u, v);
   op(tree_pos[u], tree_pos[v]);
}
