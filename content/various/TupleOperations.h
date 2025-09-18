/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Common operations with std::tuple.
 * Usage: See examples below
 * Time: O(1) for most operations
 */
#pragma once

// Creating tuples
tuple$<$int,char$>$ foo(10,'x');
auto bar = make_tuple("test", 3.1, 14, 'y');
// Accessing elements
get$<$2$>$(bar) = 100; //Access and modify element

// Unpacking tuples
int myint; char mychar;
tie(myint, mychar) = foo; // Unpack elements
tie(ignore, ignore, myint, mychar) = bar; // Unpack (with ignore)

// Getting tuple size
constexpr size_t size = tuple_size$<$decltype(tup)$>$::value;  // Number of elements

// Swapping tuples
tup1.swap(tup2);  // Swap tup1 values with tup2

// Concatenating tuples
tuple$<$int,char,float$>$ tup1(20,'g',17.5);
tuple$<$int,char,float$>$ tup2(30,'f',10.5);
auto tup3 = tuple_cat(tup1,tup2);  // Concatenate to create new tuple 