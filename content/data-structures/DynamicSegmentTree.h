/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Dynamic Segment Tree
 * Usage: NODE *root = new NODE(); upd(root, 0, N-1, pos, delta); query(root, 0, N-1, L, R);
 */
#pragma once

//Dynamic ST
struct NODE {
  int v;
  NODE *l, *r;
};

void upd(NODE *node, int b, int e, int i, int v) {
  if (b > i || e < i) return;
  if (b == e) return void(node->v += v);
  int mid = (b + e) / 2;
  if (i <= mid) {
    if (!node->l) node->l = new NODE();
    upd(node->l, b, mid, i, v);
  }
  else {
    if (!node->r) node->r = new NODE();
    upd(node->r, mid + 1, e, i, v);
  }
  node->v = (node->l ? node->l->v : 0) + (node->r ? node->r->v : 0);
}

int query(NODE *node, int b, int e, int l, int r) {
  if (b > r || e < l || node == nullptr) return 0;
  if (b >= l && e <= r) return node->v;
  int mid = (b + e) / 2;
  return query(node->l, b, mid, l, r) + query(node->r, mid + 1, e, l, r);
} 