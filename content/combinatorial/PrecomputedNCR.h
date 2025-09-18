/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Precomputed binomial coefficients with modular arithmetic.
 * Calculates nCr mod MOD for n,r < N using precomputed factorials.
 * Time: O(N) preprocessing, O(1) per query
 * Status: Tested
 */
#pragma once

int C(int n, int r) {
    if (r > n) return 0;
    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}

void prepare() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    ifact[N - 1] = inv(fact[N - 1]); //inv is a function that returns the modular inverse of a number
    for (int i = N - 2; i >= 0; i--) {
        ifact[i] = (ifact[i + 1] * (i + 1)) % mod;
    }
} 