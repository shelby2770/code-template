/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: \texttt{update(i,x): a[i] += x;}\\
 * \texttt{query(i): sum in [0, i);}\\
 * \texttt{lower\_bound(sum): min pos st sum of [0, pos] >= sum, returns n if all < sum, or -1 if empty sum.}
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

struct FT {
  int n; V<ll> s;
	FT(int _n) : n(_n), s(_n) {}
	void update(int i, ll x) { 
    for (; i < n; i |= i + 1) s[i] += x; }
	ll query(int i, ll r = 0) { 
    for (; i > 0; i &= i - 1) r += s[i-1]; return r; }
	int lower_bound(ll sum) {
		if (sum <= 0) return -1; int pos = 0;
    for (int pw = 1 << __lg(n); pw; pw >>= 1){
      if (pos+pw <= n && s[pos + pw-1] < sum)
        pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
}; // Hash = d05c4f without lower_bound
