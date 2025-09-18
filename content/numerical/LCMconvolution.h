/**
 * Author: Unknown
 * Source: https://judge.yosupo.jp/submission/79202
 * Description: Computes $c_1, ..., c_n$, where $c_k = \sum_{lcm(i, j) = k} a_i b_j$. Generate all primes upto n into pr first using sieve.
 * Time: $\mathcal{O}(N \log \log N)$
 * Status: stress-tested
 */
 
void fw_div_transform (V<ll> &a) {
  int n = sz(a) - 1;
  for (const auto p : pr) {
    if (p > n) break;
    for (int i=1; i*p <= n; ++i) a[i*p]+=a[i];
} } // A[i] = \sum_{d | i} a[d]
void bw_div_transform (V<ll> &a) {
  int n = sz(a) - 1;
  for (const auto p : pr) {
    if (p > n) break;
    for (int i=n/p; i>0; --i) a[i*p]-=a[i];
} } // From A get a
V<ll>lcm_conv (const V<ll>&a, const V<ll>&b){
  assert(sz(a) == sz(b)); int n = sz(a);
  auto A = a, B = b;
  fw_div_transform(A); fw_div_transform(B);
  for (int i = 1; i < n; ++i) A[i] *= B[i];
  bw_div_transform(A); return A;
}
