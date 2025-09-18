/**
 * Author: Arman Ferdous
 * Date: 2025-06-16
 * Description: 
 */
#include <bits/stdc++.h> /** keep-include */
using namespace std;
#define TT template <typename T

TT,typename=void> struct cerrok:false_type {};
TT> struct cerrok <T, void_t<decltype(cerr << declval<T>() )>> : true_type {};

TT> constexpr void p1 (const T &x);
TT, typename V> void p1(const pair<T, V> &x) {
  cerr << "{"; p1(x.first); cerr << ", "; 
  p1(x.second); cerr << "}"; 
}
TT> constexpr void p1 (const T &x) {
  if constexpr (cerrok<T>::value) cerr << x;
  else if constexpr (requires { std::declval<T&>().pop(); }) {
    auto tmp = x;
    int f = 0;
    cerr << "{";
    while (!tmp.empty()) {
      cerr << (f++ ? ", " : "");
      if constexpr (requires { tmp.top(); }) p1(tmp.top());    
      else p1(tmp.front());
      tmp.pop();
    }
    cerr << "}";
  }
  else { int f = 0; cerr << '{';
    for (auto &i: x) 
      cerr << (f++ ? ", " : ""), p1(i);
    cerr << "}";
} }
void p2() { cerr << "]\n"; }
TT, typename... V> void p2(T t, V... v) {
  p1(t);
  if (sizeof...(v)) cerr << ", ";
  p2(v...);
}

#ifdef LOCAL
#define debug(x...) {cerr <<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; p2(x);}
#define dbg(x, len) {cerr << __func__ << ":" << __LINE__<< " [" << #x << "] = {";for (int i = 0; i < (len); ++i) {if (i) cerr << ", ";p1((x)[i]);}cerr << "}\n";} 
#endif
