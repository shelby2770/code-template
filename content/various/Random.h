/**
 * Author: Ruhan Habib
 * Date:
 * License: 
 * Source:
 * Description: Nice uniform real/int distribution wrapper
 * Time: 
 * Status: untested
 */

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use mt19937_64 for long long
uniform_int_distribution<int> dist1(lo, hi);
uniform_real_distribution<> dist2(lo, hi);
// Usage
#define rand(l,r) uniform_int_distribution<ll>(l, r)(rng_64)
int val = rng(), val3 = dist1(rng);
ll val2 = rng_64(); double val4 = dist2(rng);
shuffle(vec.begin(), vec.end(), rng);
