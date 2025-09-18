/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: XOR Hashing for array elements.
 * Maps each unique value to a random number and computes prefix XOR sums.
 * Useful for subarray XOR queries and finding subarrays with given XOR.
 * Time: O(n log n) for preprocessing, O(1) for queries
 */
#pragma once

void xorHashing(vector<int>& v) {
  map<int, int> hash;
  hash[0] = 0;
  set<int> used = {0};
  int n = v.size();
  vector<int> pref(n + 1);
  
  for (auto &it: v) {
    int random;
    if (!hash.count(it)) {
      do {
        random = rng();
      } while (used.count(random));
      used.insert(random);
      hash[it] = random;
    }
    else random = hash[it];
    it = random;
  }
  
  for (int i = 1; i <= n; ++i) {
    pref[i] = pref[i - 1] ^ v[i-1];
  }
  
  // Now pref[r+1] ^ pref[l] gives XOR of v[l...r]
} 