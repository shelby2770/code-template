/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge. A node 
 *  is a cut point if (1) Exists in multiple bccs, or (2) Endpoint of a bridge with 
 *  degree > 1 (self loops don't count as degree).
 * Usage:
 *  int eid = 0; g.resize(N);
 *  for each edge (a,b) {
 *    g[a].emplace_back(b, eid);
 *    g[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

vector<vector<pii>> g;
vi num, st; int Time;
template<class F>
int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, top = me;
	for (auto [y, e] : g[at]) if (e != par) {
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me) st.push_back(e);
		} else {
			int si = sz(st), up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { /* e is a bridge */ }
  } }
	return top;
}
template<class F> void bicomps(F f) {
  Time = 0; num.assign(sz(g), 0);
	rep(i,0,sz(g)) if (!num[i]) dfs(i, -1, f);
}
