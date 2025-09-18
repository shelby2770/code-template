/**
 * Author: Arman Ferdous
 * Date: 2025-06-18
 * License: CC0
 * Source: DrSwad blog
 * Description: Maintain the basis of bit vectors.
 * Time: $O(D^2/64)$ per insert
 */
const int D = 1000; // use ll if < 64
struct Xor_Basis {
  V<int> who; V<bitset<D>> a;
  Xor_Basis () : who(D, -1) {}
  bool insert (bitset<D> x) {
    for (int i = 0; i < D; ++i) 
      if (x[i] && who[i]!=-1) x^=a[who[i]];
    int pivot = -1;
    for (int i = 0; i < D; ++i) 
      if (x[i]) { pivot = i; break; }
    if (pivot == -1) return false;
    // ^ null vector detected
    who[pivot] = sz(a);
    for (int i = 0; i < sz(a); ++i) 
      if (a[i][pivot] == 1) a[i] ^= x;
    a.push_back(x);
    return true;
  }
};
