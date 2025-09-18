/**
 * Author:
 * Date: 2025-06-20
 * Source: CP Algorithms
 * Description: Sequence of binary strings where each successive values differ in only 1 bit. Can be used to find Hamiltonian cycle on $n$-dimensional hypercube by calling $g(0), ..., g(2^n-1)$. 
 */

int g (int n) { return n ^ (n >> 1); }
int rev_g (int g) { int n = 0;
  for (; g; g >>= 1) n ^= g;
  return n; 
}

