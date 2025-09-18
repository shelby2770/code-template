/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Coordinate compression to map values to a continuous range [0...N-1].
 * Usage: 
 *   vector$<$int$>$ a = {10, 100, 5, 1000};
 *   // After compression: a = {1, 2, 0, 3}
 * Time: O(n log n)
 */
#pragma once

vector<int> a = v;
map<T, int> mp;
int cnt = 0;
for (auto &it : a) mp[it];
for (auto &it : mp) it.second = cnt++;
for (auto &it : a) it = mp[it]; 