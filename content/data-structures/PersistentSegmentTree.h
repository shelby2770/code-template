/**
 * Author: Istiaque
 * Date:
 * License:
 * Source: 
 * Description: Persistent segment tree implementation. Each update creates a new version of 
 * the tree while preserving the previous versions. (0 based indexing)
 * Time: O(log n) per query/update
 * Status: Tested
 */

const int N = 2e5 + 9;

struct Node {
  Node *left, *right;
  ll sum;
  Node() : left(nullptr), right(nullptr), sum(0) {}
  Node(Node* l, Node* r, ll val) : left(l), right(r), sum(val) {}
};

// Build initial tree from array
Node* build(int l, int r, vector<int>& arr) {
  if (l == r)
    return new Node(nullptr, nullptr, arr[l]);
      
  int mid = (l + r) / 2;
  Node* left_child = build(l, mid, arr);
  Node* right_child = build(mid + 1, r, arr);
  
  return new Node(left_child, right_child, left_child->sum + right_child->sum);
}

// Create a new version with updated value at position
Node* update(Node* node, int l, int r, int pos, int val) {
  if (l == r)
    return new Node(nullptr, nullptr, val);
      
  int mid = (l + r) / 2;
  if (pos <= mid) {
    Node* new_left = update(node->left, l, mid, pos, val);
    return new Node(new_left, node->right, new_left->sum + node->right->sum);
  } else {
    Node* new_right = update(node->right, mid + 1, r, pos, val);
    return new Node(node->left, new_right, node->left->sum + new_right->sum);
  }
}

// Query sum in range [ql, qr] on a specific version of the tree
ll query(Node* node, int l, int r, int ql, int qr) {
  if (ql > r || qr < l) 
    return 0;
  if (ql <= l && r <= qr) 
    return node->sum;
      
  int mid = (l + r) / 2;
  return query(node->left, l, mid, ql, qr) + 
         query(node->right, mid + 1, r, ql, qr);
}

/*
Example usage:
int main() {
  int n = 5;
  vector<int> arr = {1, 2, 3, 4, 5};
  
  // Build initial tree (version 0)
  Node* version0 = build(0, n-1, arr);
  
  // Create version 1 by updating arr[2] to 10
  Node* version1 = update(version0, 0, n-1, 2, 10);
  
  // Query both versions
  ll sum_v0 = query(version0, 0, n-1, 1, 3); // Sum of elements [1,2,3] in version 0
  ll sum_v1 = query(version1, 0, n-1, 1, 3); // Sum of elements [1,2,3] in version 1
  
  cout << "Sum in version 0: " << sum_v0 << '\n'; // Output: 9
  cout << "Sum in version 1: " << sum_v1 << '\n'; // Output: 16
  
  return 0;
}
*/ 