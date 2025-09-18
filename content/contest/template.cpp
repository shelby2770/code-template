/**
 * Author: Arman Ferdous
 * Date: 2025-06-16
 * Description: 
 */

#include "bits/stdc++.h"
#ifndef LOCAL
#define dbg(...)
#define debug(...)
#endif

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

using namespace std;
#define int long long
#define sz(v) (int)(v).size()
#define all(v) begin(v),end(v)
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define cinv(v) for (auto &it:v) cin>>it;
#define coutv(v) for (auto &it:v) cout<< it<<' '; cout<<'\n';
#define unique(v) sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
template<class T> using V = vector<T>;
// template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve(int tc) {
    
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) shelby(_);
}