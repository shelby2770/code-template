/**
 * Author: Online
 * Date: 2019-05-22
 * License: CC0
 * Description: Can be used to precompute multiplicative functions using $f(px) = f(p)f(x)$ when $p \nmid x$. We compute $f(px) = f(p^{e+1} \cdot x / p^e) = f(p^{e + 1})f(x / p^e)$ by multiplicativity (bookkeeping e, the max power of $p$ dividing $x$ where $p$ is the smallest prime dividing $x$). If $f(px)$ can be computed easily when $p \mid x$ then we can simplify the code. 
 * Time: $O(n)$
 * Status: Works
 */
int func[N],cnt[N]; bool isc[N]; V<int> prime;
void sieve (int n) {
  fill(isc, isc + n, false); func[1] = 1;
  for (int i = 2; i < n; ++i) {
    if (!isc[i]) {
      prime.push_back(i); func[i]=1; cnt[i]=1;
    }
    for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
      isc[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        func[i * prime[j]] = func[i] / cnt[i] * (cnt[i] + 1);
        cnt[i * prime[j]] = cnt[i] + 1; break;
      } else {
        func[i * prime[j]] = func[i] * func[prime[j]];
        cnt[i * prime[j]] = 1;
} } } }
