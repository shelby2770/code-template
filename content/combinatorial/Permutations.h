/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Permutation algorithms
 * Time: O(n!)
 */
#pragma once

void permute(string &s, int l, int r) {
  if (l == r) { cout << s << '\n'; return; }
  for (int i = l; i <= r; ++i) {
    swap(s[l], s[i]);
    permute(s, l + 1, r);
    swap(s[l], s[i]);
  }
}

// STL: sort(all(v)); do{/*process*/}while(next_permutation(all(v)));
// For prev_permutation, start with reverse sorted 