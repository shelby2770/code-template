/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Custom comparators for priority queues, sets, and sorting.
 * Usage: See code examples below
 * Time: O(nlogn) 
 */
#pragma once

struct cmp {
    bool operator()(const pair<int, int> &i, const pair<int, int> &j) const {
        return i.second < j.second;
    }
};
// sort(v.begin(), v.end(), [&](auto i, auto j) -> bool {return i[1] < j[1];});

