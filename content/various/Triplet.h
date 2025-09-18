/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: A triplet struct with operator overloading for +, =, and ==.
 * Usage: triplet t(1, 2, 3); triplet t2 = t + triplet(4, 5, 6);
 * Time: O(1)
 */
#pragma once

struct triplet {
  int a, b, c;
  triplet(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
  triplet &operator=(const triplet &obj) {
    a = obj.a, b = obj.b;
    return *this;
  }
  triplet operator+(const triplet &obj) const {
    return triplet(a + obj.a, b + obj.b, c + obj.c);
  }
  bool operator==(const triplet &obj) const {
    return (a == obj.a && b == obj.b);
  }
}; 