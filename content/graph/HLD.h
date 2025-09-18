/**
 * Author: Istiaque
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Heavy-Light Decomposition (HLD) for efficient path queries on trees.
 * Decomposes a tree into paths where a path from any node to the root traverses at most log(n) paths.
 * Usage: Process queries like finding max/min/sum on paths between nodes or updating node values.
 * Time: O(log n) per query/update, O(n) for preprocessing
 * Status: Tested
 */

const int N = 2e5 + 9, LG = 18;
 
struct ST {
	//include SegmentTreeIterative.h
} t;
 
vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];
 
void dfs(int u, int p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  if (p) g[u].erase(find(g[u].begin(), g[u].end(), p));
  for (auto &v: g[u])
    if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}
 
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
 
int kth(int u, int k) {
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
  return u;
}
 
int T, arr[N], head[N], st[N], en[N];
 
void dfs_hld(int u) {
  st[u] = ++T;
  for (auto v: g[u]) {
    head[v] = (v == g[u][0] ? head[u] : v);
    dfs_hld(v);
  }
  en[u] = T;
}
 
int n, q;
 
int query_up(int u, int v) {
  int ans = 0;
  while (head[u] != head[v]) {
    ans = max(ans, t.query(st[head[u]], st[u]));
    u = par[head[u]][0];
  }
  ans = max(ans, t.query(st[v], st[u]));
  return ans;
}
 
int query(int u, int v) {
  int l = lca(u, v);
  int ans = query_up(u, l);
  if (v != l) ans = max(ans, query_up(v, kth(v, dep[v] - dep[l] - 1)));
  return ans;
}
 
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> arr[i];
 
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  head[1] = 1;
  dfs_hld(1);
  t.n = n;
  t.t.assign(2 * n + 1, 0);
  for (int i = 1; i <= n; ++i) t.upd(st[i], arr[i]);
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int s, x;
      cin >> s >> x;
      t.upd(st[s], x);
    }
    else {
      int a, b;
      cin >> a >> b;
      cout << query(a, b) << ' ';
    }
  }
}