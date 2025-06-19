/**
 * Author: Ruhan Habib
 * Date: 2024
 * License:
 * Source:
 * Description: Not so fast Voronoi from FastDelaunay
 * Assumes that there are no duplicate points and that not all points are on a single line.
 * Each circumcircle contains none of the input points.
 * Should work for doubles as well, but haven't checked
 * This can be optimized to use much less memory if needed. Also manually fix BIG.
 * Time: O(n \log n)
 * Status:
 */
#pragma once

#include "FastDelaunay.h"

struct voronoi_graph {
 using P = Point<ll>;
 using Pd = Point<double>;

 const double BIG = 1e8;

 static Pd promote (P p) { return Pd(p.x, p.y); }

 vector<tuple<P,P,P>> nodes;
 vector<vector<tuple<pair<P,P>, int, Pd>>> adj;
  // ((A, B), v, Direction)
  // the edge, when extended to a line, is the perpendicular bisector of the segment AB
  // v is the index of the adjacent node. it is -1 if the edge goes to infty
  // circumcenter(node) + Direction gives us the other vertex

 voronoi_graph (const vector<P>& pts) {
  auto t = delaunay::triangulate(pts);
  assert (sz(t) % 3 == 0);
  nodes.resize(sz(t) / 3);
  for (int i = 0; i < sz(t); i += 3)
   nodes[i / 3] = {t[i], t[i+1], t[i+2]};
  sort(all(nodes));
  adj.resize(sz(nodes));

  vector<pair<pair<P,P>, tuple<P,P,P>>> delaunay_edges;
  delaunay_edges.reserve(sz(t));
  for (int i = 0; i < sz(t); i += 3) {
   for (int j = i; j < i + 3; j++)
    for (int k = j + 1; k < i + 3; k++)
     delaunay_edges.emplace_back(pair(min(t[j], t[k]), max(t[j], t[k])), tuple(t[i], t[i+1], t[i+2]));
  }
  sort(all(delaunay_edges));

  for (int i = 0; i < sz(delaunay_edges); i++) {
   const int x = lower_bound(all(nodes), delaunay_edges[i].second) - nodes.begin();
   auto [a,b,c] = delaunay_edges[i].second;
   if (c == delaunay_edges[i].first.first || c == delaunay_edges[i].first.second)
    swap(b, c);
   if (c == delaunay_edges[i].first.first || c == delaunay_edges[i].first.second)
    swap(a, c);
   if (c == delaunay_edges[i].first.first || c == delaunay_edges[i].first.second)
    assert (false);

   if (i+1 < sz(delaunay_edges) && delaunay_edges[i+1].first == delaunay_edges[i].first) {
    const int y = lower_bound(all(nodes), delaunay_edges[i+1].second) - nodes.begin();
    auto dir = get_vertex(y) - get_vertex(x);
    adj[x].emplace_back(delaunay_edges[i].first, y, dir);
    adj[y].emplace_back(delaunay_edges[i].first, x, dir * (-1.0));
   } else if (i == 0 || delaunay_edges[i-1].first != delaunay_edges[i].first) {
    bool out = (a - c).dot(b - c) < 0;
    auto dir = ((promote(a + b) / 2.0) - get_vertex(x)) * (out ? -1.0 : 1.0);
    adj[x].emplace_back(delaunay_edges[i].first, -1, dir * BIG);
   }
  }
 }

 Pd get_vertex (int i) {
  auto [a, b, c] = nodes[i];
  return ccCenter(promote(a), promote(b), promote(c));
 }

 pair<Pd,Pd> get_edge (int i, int j) {
  const Pd vi = get_vertex(i);
  return {vi, vi + get<2>(adj[i][j])};
 }
};
