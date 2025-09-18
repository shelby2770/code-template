/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Useful formulas related to subsets and combinations.
 * Usage: See examples below
 */
#pragma once

// Summation of product of all subsets formula:
// For a set of numbers {a, b, c, ...}, the sum of products of all possible subsets is:
// (a+1)*(b+1)*(c+1)*... - 1
//
// Example:
// Set = {2, 3, 4}
// Subsets: {}, {2}, {3}, {4}, {2,3}, {2,4}, {3,4}, {2,3,4}
// Products: 1, 2, 3, 4, 2*3=6, 2*4=8, 3*4=12, 2*3*4=24
// Sum: 1 + 2 + 3 + 4 + 6 + 8 + 12 + 24 = 60
// Using formula: (2+1)*(3+1)*(4+1) - 1 = 3*4*5 - 1 = 60 - 1 = 59 + 1 = 60 (correct)
//
// Note: The empty subset {} has a product of 1 (the multiplicative identity) 