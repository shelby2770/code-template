/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ordered_set<T> o;
template <typename T, typename R>
using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//for ordered multiset "upper_bound" and "lower_bound" are reversed
//o.erase(--(o.lower_bound(v[i])))
//order_of_key: The number of items in a set that are strictly smaller than k
//find_by_order: It returns an iterator to the ith largest element

template<class T> using Tree=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void example() {
	Tree<int> t, t2; t.insert(8);
	auto it = t.insert(10).first;
	assert(it == t.lower_bound(9));
	assert(t.order_of_key(10) == 1);
	assert(t.order_of_key(11) == 2);
	assert(*t.find_by_order(0) == 8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}
