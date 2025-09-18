/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Common vector operations like removing duplicates.
 * Usage: 
 *   vector$<$int$>$ v = {3, 1, 4, 1, 5, 9};
 *   sortAndUnique(v); // v = {1, 3, 4, 5, 9}
 * Time: O(n log n) for sorting, O(n) for unique
 */
#pragma once

sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end()); 