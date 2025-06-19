/**
 * Author: CP Algo, with modifications by Arman
 * Date:
 * License:
 * Source: https://cp-algorithms.com/graph/bridge-earching.html
 * Description: Only need to call \texttt{PointsAndBridges()}. Nodes are $[0,n)$ which can easily
 *              be configured there.
 * Time: $\mathcal{O}(V + E)$ except the final sorting of bridges. If the graph doesn't contain any multi-edges, that part can be omitted. 
 * Status: Tested
 */

vector<bool> vis, cutPoint;
vi low, disc; int tim;
vector<pair<int,int>> mebi, bridge;

void dfsPB(int u, int f = -1) {
  vis[u] = true; int children = 0;
  disc[u] = low[u] = tim++;
  for (int v : g[u]) {
    if (v == f) continue; // all loops ignored
    if (vis[v]) low[u] = min(low[u], disc[v]);
    else {
      dfsPB(v, u); ++children;
      low[u] = min(low[u], low[v]);

      if (disc[u] < low[v]) {
        // u === v if no multi edges.
        mebi.pb({min(u, v), max(u, v)});
      }
      if (disc[u] <= low[v]  && f != -1)
        cutPoint[u] = true;//this line executes > once
    }
  }
  if (f == -1 && children > 1) cutPoint[u] = 1;
}

void PointsAndBridges() { // [0,n)
  vis.assign(n, false); tim = 0;
  low.assign(n, -1); disc.assign(n, -1);
  cutPoint.assign(n, false); mebi.clear();

  for (int i = 0; i < n; ++i)
    if (!vis[i]) dfsPB(i);

  sort(all(mebi)); bridge.clear();
  for (int i = 0; i < sz(mebi); ++i) {
    if ((i + 1 < sz(mebi) && mebi[i + 1] == mebi[i]) 
      || (i > 0 && mebi[i - 1] == mebi[i])) continue;
    bridge.pb(mebi[i]);
  }
}
