/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Mo's Algorithm with block sorting.
 * Time: O(N \sqrt{Q})
 * Status: Tested
 */
#pragma once

void mo_s_algorithm() {
  int n = /* array size */;
  int block_sz = sqrt(n);
  sort(queries.begin(), queries.end(), [&](auto i, auto j) -> bool {
    return make_pair(i.first.first / block_sz, i.first.second) <
           make_pair(j.first.first / block_sz, j.first.second);
  });
  int curr_l = 0, curr_r = -1;
  for (auto query : queries) {
    int l = query.first.first, r = query.first.second;
    while (l < curr_l) curr_l--;
    while (l > curr_l) curr_l++;
    while (r > curr_r) curr_r++;
    while (r < curr_r) curr_r--;
    // answers[query.second] = current_result;
  }
} 