/**
 * Author: Unknown
 * Source: https://judge.yosupo.jp/submission/79202
 * Description: Computes $c_1, ..., c_n$, where $c_k = \sum_{\gcd(i, j) = k} a_i b_j$. Generate all primes upto n into pr first using sieve.
 * Time: $\mathcal{O}(N \log \log N)$
 * Status: stress-tested
 */
 
void fw_mul_transform (V<ll> &a) {
  int n = sz(a) - 1;
  for (const auto p : pr) {
    if (p > n) break;
    for (int i = n/p; i>0; --i) a[i]+=a[i*p];
} } // A[i] = \sum_{j} a[i * j]
void bw_mul_transform (V<ll> &a) {
  int n = sz(a) - 1;
  for (const auto p : pr) {
    if (p > n) break;
    for (int i=1; i*p <= n; ++i) a[i]-=a[i*p];
} } // From A get a
V<ll>gcd_conv (const V<ll>&a, const V<ll>&b){
  assert(sz(a) == sz(b)); int n = sz(a);
  auto A = a, B = b;
  fw_mul_transform(A); fw_mul_transform(B);
  for (int i = 1; i < n; ++i) A[i] *= B[i];
  bw_mul_transform(A); return A;
}
