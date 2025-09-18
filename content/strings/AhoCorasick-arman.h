/**
 * Author: Arman Ferdous
 * Date:
 * License:
 * Source: 
 * Description: 
 * Usage: insert strings first (0-indexed). Then call prepare to use everything. link = suffix link. to[ch] = trie transition. jump[ch] = aho transition to ch using links.
 * Time: $\mathcal{O}(AL)$
 * Status: Tested
 */

const int L = 5000; // Total no of characters
const int A = 10; // Alphabet size

struct Aho_Corasick {
  struct Node {
    bool end_flag; 
    int par, pch, to[A], link, jump[A];
    Node() {
      par = link = end_flag = 0;
      memset(to, 0, sizeof to);
      memset(jump, 0, sizeof jump);
    }
  }; Node t[L]; int at;
  Aho_Corasick() { at = 0; }

  void insert(string &s) {
    int u = 0;
    for (auto ch : s) {
      int &v = t[u].to[ch - '0'];
      if (!v) v = ++at;
      t[v].par = u; t[v].pch = ch - '0'; u=v;
    } t[u].end_flag = true;
  }
  void prepare() {
    for(queue<int>q({0});!q.empty();q.pop()){
      int u = q.front(), w = t[u].link;
      for (int ch = 0; ch < A; ++ch) {
        int v = t[u].to[ch];
        if (v) { 
          t[v].link = t[w].jump[ch];
          q.push(v);
        }
        t[u].jump[ch] = v ? v : t[w].jump[ch];
  } } }
}aho;
