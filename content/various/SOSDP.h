/**
 * Author: Istiaque
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Sum Over Subsets (SOS) DP implementation.
 * Technique for efficiently calculating functions over subsets or supersets of bitmasks.
 * Time: O(N * 2^N) for preprocessing, O(1) for queries
 * Status: Tested
 */
#pragma once

const int B = 20; // Maximum number of bits (adjust as needed)

// Precomputes sum over all subsets of masks
// After this, f[mask] = sum of f[submask] for all submask <= mask
void precomputeSubsetSums(vector<int>& f, int bits = B) {
  for (int i = 0; i < bits; i++) {
    for (int mask = 0; mask < (1 << bits); mask++) {
      if (mask & (1 << i)) {
        f[mask] += f[mask ^ (1 << i)];
      }
    }
  }
}

// Precomputes sum over all supersets of masks
// After this, g[mask] = sum of g[supermask] for all mask <= supermask
void precomputeSupersetSums(vector<int>& g, int bits = B) {
  for (int i = 0; i < bits; i++) {
    for (int mask = (1 << bits) - 1; mask >= 0; mask--) {
      if ((mask & (1 << i)) == 0) {
        g[mask] += g[mask ^ (1 << i)];
      }
    }
  }
}

// Alternative implementation with better constant factor
// Precomputes sum over all subsets of masks in O(N * 2^N)
void fastSubsetSums(vector<int>& f, int bits = B) {
  for (int i = 0; i < bits; i++) {
    for (int mask = 0; mask < (1 << bits); mask++) {
      if ((mask & (1 << i)) == 0) {
        f[mask | (1 << i)] += f[mask];
      }
    }
  }
}

// Alternative implementation with better constant factor
// Precomputes sum over all supersets of masks in O(N * 2^N)
void fastSupersetSums(vector<int>& g, int bits = B) {
  for (int i = 0; i < bits; i++) {
    for (int mask = 0; mask < (1 << bits); mask++) {
      if (mask & (1 << i)) {
        g[mask ^ (1 << i)] += g[mask];
      }
    }
  }
} 