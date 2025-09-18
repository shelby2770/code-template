/**
 * Author: 
 * Date: 2025-06-19
 * Source: Taken from DU_Ascending template
 * Description: Finds the block-cut tree of a bidirectional graph. Tree nodes
 * are either cut points or a block. All edges are between a block and a cut point. 
 * Combining all nodes in a block with its neighbor cut points give the whole BCC.
 * Usage: art[i] = true if cut point. Cut-points are relabeled within [1,ncut]. Higher
 * labels are for blocks. Resets: art, g[1,n], tree[1,ptr], st, comp[1,cur], ptr, cur, in;
 * Status: tested
 */
bitset <N> art;
vector <int> g[N], tree[N], st, comp[N];
int n, m, ptr, cur, ncut, in[N],low[N],id[N];
void dfs (int u, int from = -1) {
  in[u] = low[u] = ++ptr; st.emplace_back(u);
  for (int v : g[u]) if (v ^ from) {
    if (!in[v]) {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= in[u]) {
        art[u] = in[u] > 1 or in[v] > 2;
        comp[++cur].emplace_back(u);
        while (comp[cur].back() ^ v) {
          comp[cur].emplace_back(st.back());
          st.pop_back();
      } }
    } else { low[u] = min(low[u], in[v]); }
} }
void buildTree() {
  ptr = 0;
  for (int i = 1; i <= n; ++i) {
    if (art[i]) id[i] = ++ptr;
  } ncut = ptr;
  for (int i = 1; i <= cur; ++i) {
    int x = ++ptr;
    for (int u : comp[i]) {
      if (art[u]) {
        tree[x].emplace_back(id[u]);
        tree[id[u]].emplace_back(x);
      } else { id[u] = x; }
} } }
int main() {
  for (int i = 1; i <= n; ++i) 
    if (!in[i]) dfs(i);
  buildTree();
}
