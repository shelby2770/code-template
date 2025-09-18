/**
 * Author: Istiaque
 * Date:
 * License:
 * Source: 
 * Description: Suffix Automaton implementation for string processing.
 * A suffix automaton is a minimal DFA that recognizes all suffixes of a string.
 * Useful for substring queries, pattern matching, and counting unique substrings. 
 * Time: O(n) for construction, where n is the string length
 * Status: Tested
 */


// Suffix Automaton Structure
// len -> largest string length of the corresponding endpos-equivalent class
// link -> longest suffix that is another endpos-equivalent class.
// firstpos -> 1 indexed end position of the first occurrence of the largest string of that node
// minlen(v) -> smallest string of node v = len(link(v)) + 1
// terminal nodes -> store the suffixes
struct SuffixAutomaton {
  struct node {
    int len, link, firstpos;
    map<char, int> nxt;
  };
  int sz, last;
  vector<node> t;
  vector<int> terminal;
  vector<long long> dp;
  vector<vector<int>> g;
  
  SuffixAutomaton() {}
  
  SuffixAutomaton(int n) {
    t.resize(2 * n); 
    terminal.resize(2 * n, 0);
    dp.resize(2 * n, -1); 
    sz = 1; 
    last = 0;
    g.resize(2 * n);
    t[0].len = 0; 
    t[0].link = -1; 
    t[0].firstpos = 0;
  }
  
  void extend(char c) {
    int p = last;
    if (t[p].nxt.count(c)) {
      int q = t[p].nxt[c];
      if (t[q].len == t[p].len + 1) {
        last = q;
        return;
      }
      int clone = sz++;
      t[clone] = t[q];
      t[clone].len = t[p].len + 1;
      t[q].link = clone;
      last = clone;
      while (p != -1 && t[p].nxt[c] == q) {
        t[p].nxt[c] = clone;
        p = t[p].link;
      }
      return;
    }
    int cur = sz++;
    t[cur].len = t[last].len + 1;
    t[cur].firstpos = t[cur].len;
    p = last;
    while (p != -1 && !t[p].nxt.count(c)) {
      t[p].nxt[c] = cur;
      p = t[p].link;
    }
    if (p == -1) t[cur].link = 0;
    else {
      int q = t[p].nxt[c];
      if (t[p].len + 1 == t[q].len) t[cur].link = q;
      else {
        int clone = sz++;
        t[clone] = t[q];
        t[clone].len = t[p].len + 1;
        while (p != -1 && t[p].nxt[c] == q) {
          t[p].nxt[c] = clone;
          p = t[p].link;
        }
        t[q].link = t[cur].link = clone;
      }
    }
    last = cur;
  }
  
  // Build the suffix link tree
  void build_tree() {
    for (int i = 1; i < sz; i++) g[t[i].link].push_back(i);
  }
  
  // Build the automaton from a string
  void build(string &s) {
    for (auto x: s) {
      extend(x);
      terminal[last] = 1;
    }
    build_tree();
  }
  
  // Count the number of times i-th node occurs in the string
  long long cnt(int i) {
    if (dp[i] != -1) return dp[i];
    long long ret = terminal[i];
    for (auto &x: g[i]) ret += cnt(x);
    return dp[i] = ret;
  }
  
  // Count the total number of unique substrings
  long long countUniqueSubstrings() {
    long long ans = 0;
    for (int i = 1; i < sz; i++) {
      ans += t[i].len - t[t[i].link].len;
    }
    return ans;
  }
  
  // Check if a pattern exists in the original string
  bool exists(string &pattern) {
    int cur = 0;
    for (char c : pattern) {
      if (!t[cur].nxt.count(c)) return false;
      cur = t[cur].nxt[c];
    }
    return true;
  }
  
  // Find the first occurrence of a pattern in the original string
  // Returns the end position (1-indexed) or -1 if not found
  int findFirstOccurrence(string &pattern) {
    int cur = 0;
    for (char c : pattern) {
      if (!t[cur].nxt.count(c)) return -1;
      cur = t[cur].nxt[c];
    }
    // Return the end position of the first occurrence
    return t[cur].firstpos;
  }
  
  // Count the number of occurrences of a pattern in the original string
  long long countOccurrences(string &pattern) {
    int cur = 0;
    for (char c : pattern) {
      if (!t[cur].nxt.count(c)) return 0;
      cur = t[cur].nxt[c];
    }
    return cnt(cur);
  }
  
  // Find the longest common substring with another string
  string longestCommonSubstring(string &s2) {
    int v = 0, len = 0, best = 0, bestpos = 0;
    for (int i = 0; i < s2.size(); i++) {
      while (v && !t[v].nxt.count(s2[i])) {
        v = t[v].link;
        len = t[v].len;
      }
      if (t[v].nxt.count(s2[i])) {
        v = t[v].nxt[s2[i]];
        len++;
      }
      if (len > best) {
        best = len;
        bestpos = i;
      }
    }
    return s2.substr(bestpos - best + 1, best);
  }
}; 