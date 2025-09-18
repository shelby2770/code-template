/**
 * Author: Istiaque
 * Date:
 * License:
 * Source: 
 * Description: Mo's Algorithm on Trees (using Euler Tour + Mo's on array) for
 * querying properties of paths between nodes such as counting distinct colors.
 * Time: O((N + Q) * sqrt(2*N)) 
 * Status: Tested
 */
 
const int N = 2e5 + 9;
vector<int> adj[N];
int color[N];
int st[N], en[N], euler[2 * N], timer;
int depth[N], up[20][N];

// For Mo
int BLOCK;

struct Query {
  int l, r, idx, lca;
};

vector<Query> queries;
long long answer[N];
int freq[N], cntDistinct;
bool inPath[N];

// Euler Tour: record entry and exit, flatten tree
void dfs(int u, int p) {
  up[0][u] = p;
  depth[u] = (p == -1 ? 0 : depth[p] + 1);
  st[u] = timer;
  euler[timer++] = u;
  for (int v: adj[u]) if (v != p) dfs(v, u);
  en[u] = timer;
  euler[timer++] = u;
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v];
  for (int i = 0; i < 20; i++) if (diff >> i & 1) u = up[i][u];
  if (u == v) return u;
  for (int i = 19; i >= 0; i--)
    if (up[i][u] != up[i][v]) {
      u = up[i][u];
      v = up[i][v];
    }
  return up[0][u];
}

// Toggle node in current window
void add(int u) {
  if (inPath[u]) {
    // remove
    freq[color[u]]--;
    if (freq[color[u]] == 0) cntDistinct--;
  }
  else {
    // add
    if (freq[color[u]] == 0) cntDistinct++;
    freq[color[u]]++;
  }
  inPath[u] = !inPath[u];
}

/*
Example usage:
int main() {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> color[i];
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  
  // Initialize data structures
  timer = 0;
  memset(up, -1, sizeof up);
  
  // Build Euler tour and LCA table
  dfs(1, -1);
  
  // Build ancestor table
  for (int i = 1; i < 20; i++)
    for (int v = 1; v <= n; v++)
      up[i][v] = (up[i-1][v] == -1 ? -1 : up[i-1][up[i-1][v]]);

  // Prepare queries
  BLOCK = sqrt(timer);
  for (int i = 0, u, v; i < q; i++) {
    cin >> u >> v;
    if (st[u] > st[v]) swap(u, v);
    int w = lca(u, v);
    if (w == u) {
      queries.push_back({st[u], st[v], i, -1});
    }
    else {
      queries.push_back({en[u], st[v], i, w});
    }
  }

  // Sort queries using Mo's algorithm ordering
  sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b) {
    if (a.l / BLOCK != b.l / BLOCK) return a.l < b.l;
    return a.r < b.r;
  });

  // Process queries
  int curL = 0, curR = -1;
  cntDistinct = 0;
  memset(freq, 0, sizeof freq);
  memset(inPath, 0, sizeof inPath);
  
  for (auto &qr: queries) {
    while (curL > qr.l) add(euler[--curL]);
    while (curR < qr.r) add(euler[++curR]);
    while (curL < qr.l) add(euler[curL++]);
    while (curR > qr.r) add(euler[curR--]);
    if (qr.lca != -1) add(qr.lca);
    answer[qr.idx] = cntDistinct;
    if (qr.lca != -1) add(qr.lca);
  }

  // Output results
  for (int i = 0; i < q; i++) cout << answer[i] << '\n';
  
  return 0;
}
*/ 