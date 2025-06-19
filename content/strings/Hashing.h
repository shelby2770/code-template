/**
 * Author: Arman Ferdous
 * Date:
 * License:
 * Source:
 * Description: Static hashing for 0-indexed string. Intervals are $[l, r]$.
 * Time: 
 * Status: Tested
 */

template<const ll M, const ll B> 
struct Hashing {
  int n; V<ll> h, pw;
  Hashing(const string &s) : n(sz(s)),h(n+1),pw(n+1) {
    pw[0] = 1; // ^^ s is 0 indexed
    for (int i = 1; i <= n; ++i)
      pw[i] = (pw[i-1] * B) % M,
      h[i] = (h[i-1] * B + s[i-1]) % M;
  }
  ll eval(int l, int r) { // assert(l <= r);
    return (h[r+1] - ((h[l] * pw[r-l+1])%M) + M)%M;
} };
struct Double_Hash {
  using H1 = Hashing<916969619, 101>;
  using H2 = Hashing<285646799, 103>;
  H1 h1; H2 h2;
  Double_Hash(const string &s):h1(s),h2(s){}
  pii eval(int l, int r) 
    { return {h1.eval(l,r), h2.eval(l,r)}; }
};
