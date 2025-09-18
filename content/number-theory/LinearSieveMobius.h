/**
 * Author: User
 * Date: 2025-09-18
 * License: CC0
 * Source: 
 * Description: Linear sieve for computing Möbius function values.
 * mu[i] = 0 if i has squared prime factor, 1 if even number of prime factors,
 * -1 if odd number of prime factors. Also computes smallest prime factors.
 * Time: O(N)
 * Status: Tested
 */
#pragma once

vector<int> lp(N), mu(N), primes;
void pre() {
  mu[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      mu[i] = -1;
      primes.push_back(i);
    }
    for (auto &j : primes) {
      int k = i * j;
      if (k >= N) break;
      if (lp[i] == j) {
        mu[k] = 0, lp[k] = j;
        break;
      }
      mu[k] = -mu[i], lp[k] = j;
    }
  }
}
