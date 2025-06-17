/**
 * Author: Arman Ferdous (inspiration: tourist, atcoder library)
 * Date:
 * License: 
 * Source:
 * Description:
 * Time: $\mathcal{O}(\log N)$
 * Status: Tested
 */
 
template<class S> struct segtree {
	int n; V<S> t;
	void init(int _) { n = _; t.assign(n+n-1, S()); }
	void init(const V<S>& v) { 
		n = sz(v); t.assign(n + n - 1, S()); 
		build(0,0,n-1,v); 
	} template <typename... T>
	void upd(int l, int r, const T&... v) {
	  assert(0 <= l && l <= r && r < n);
	  upd(0, 0, n-1, l, r, v...);
	}
	S get(int l, int r) {
    assert(0 <= l && l <= r && r < n);
    return get(0, 0, n-1, l, r);
  }
private:
	inline void push(int u, int b, int e) {
		if (t[u].lazy == 0) return;
		int mid = (b+e)>>1, rc = u+((mid-b+1)<<1);
		t[u+1].upd(b, mid, t[u].lazy);
		t[rc].upd(mid+1, e, t[u].lazy);
		t[u].lazy = 0;
	}
	void build(int u,int b,int e,const V<S>&v) {
		if (b == e) return void(t[u] = v[b]);
		int mid = (b+e)>>1, rc = u+((mid-b+1)<<1);
		build(u+1, b,mid,v); build(rc, mid+1,e,v);
		t[u] = t[u+1] + t[rc];
	} template<typename... T>
	void upd(int u, int b, int e, int l, int r, const T&... v) {
		if (l <= b && e <= r) return t[u].upd(b, e, v...);
		push(u, b, e);
		int mid = (b+e)>>1, rc = u+((mid-b+1)<<1);
		if (l<=mid) upd(u+1, b, mid, l, r, v...);
		if (mid<r) upd(rc, mid+1, e, l, r, v...);
		t[u] = t[u+1] + t[rc];
	}
	S get(int u, int b, int e, int l, int r) {
		if (l <= b && e <= r) return t[u];
		push(u, b, e); 
		S res; int mid = (b+e)>>1, rc = u+((mid-b+1)<<1);
		if (r<=mid) res = get(u+1, b, mid, l, r);
		else if (mid<l) res = get(rc,mid+1,e,l,r);
		else res = get(u+1, b, mid, l, r) + get(rc, mid+1, e, l, r);
		t[u] = t[u+1] + t[rc]; return res;
	}
}; // Hash upto here = 773c09
/* (1) Declaration:
Create a node class. Now, segtree<node> T;
T.init(10) creates everything as node()
Consider using V<node> leaves to build
(2) upd(l, r, ...v): update range [l, r]
order in ...v must be same as node.upd() fn */
struct node {
	ll sum = 0, lazy = 0;
  node () {} // write full constructor
	node operator+(const node &obj) { 
    return {sum + obj.sum, 0};    }
	void upd(int b, int e, ll x) {
		sum += (e - b + 1) * x, lazy += x;
} }; 
