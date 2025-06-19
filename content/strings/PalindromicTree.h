/**
 * Author: Arman Ferdous
 * Date:
 * License:
 * Source: https://rezwanarefin01.github.io/posts/palindromic-tree-01/ 
 * Description: Makes a trie of $\mathcal{O}(|S|)$ vertices containing all distinct palindromes
 *              of a string. Suffix links give the longest proper suffix/prefix of that palindrome
 *              which is also a palindrome.
 * Usage: $S:=$ 1-indexed string. append characters 1-by-1.
 *        After adding the ith character, ptr points to the node containing 
 *        the longest palindrome ending at $i$. Change ALPHA, ID() as problem requires.
 * Time: $\mathcal{O}(|S|)$
 * Status: Tested
 */

const int ALPHA = 26;
struct PalindromicTree {
	struct node {
		int to[ALPHA];
		int link, len;
		node(int a=0, int b=0) : link(a), len(b) {
			memset(to, 0, sizeof to);
  } };
	V<node> T; int ptr;
	int ID(char x) { return x - 'a'; }
	void init() {
		T.clear(); ptr = 1;
		T.emplace_back(0, -1); // 0=Odd root
		T.emplace_back(0, 0);  // 1=Evn root
	}
	void append(int i, string &s) {
		while (s[i - T[ptr].len - 1] != s[i]) 
			ptr = T[ptr].link;

		int id = ID(s[i]);
		// if node already exists, return
		if (T[ptr].to[id]) return void(ptr = T[ptr].to[id]);
		int tmp = T[ptr].link;
		while (s[i - T[tmp].len - 1] != s[i])
			tmp = T[tmp].link;

		int newlink = T[ptr].len == -1 ? 1 : T[tmp].to[id];
		
		// ptr is the parent of this new node
		T.emplace_back(newlink, T[ptr].len + 2);
		
		// Now shift ptr to the newly created node
		T[ptr].to[id] = sz(T) - 1;
		ptr = sz(T) - 1;
	}
};

