/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Custom hash function for unordered maps/sets to avoid hacking.
 * Uses splitmix64 algorithm and supports both integer and vector keys.
 * Usage: See code examples below
 */
#pragma once

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }

  size_t operator()(const vector<int> &v) const {
    uint64_t h = 0;
    for (int x: v) {
      h ^= splitmix64(x + 0x9e3779b97f4a7c15 + (h << 6) + (h >> 2));
    }
    return h;
  }
}; 

// Usage examples:
// unordered_map<int, int, custom_hash> safe_map;
// unordered_map<vector<int>, int, custom_hash> vector_map;