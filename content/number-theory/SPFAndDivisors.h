/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Smallest prime factor (SPF) and divisor properties.
 * SPF can be used for fast prime factorization in O(log n).
 * Time: O(N log log N) preprocessing, O(log N) factorization
 * Status: Tested
 */
#pragma once

//smallest prime factor
vector<int> spf(N);
iota(spf.begin(), spf.end(), 0);
for (int i = 2; i < N; ++i) {
  if (spf[i] == i) {
    for (int j = i * i; j < N; j += i)
      if (spf[j] == j)spf[j] = i;
  }
}

//no. of divisors= (e1+1).(e2+1).(e3+1).....(ek+1)
//sum of divisors= ((p1^(e1+1)-1)/p1-1).((p2^(e2+1)-1)/p2-1)....((pk^(ek+1)-1)/pk-1) 


