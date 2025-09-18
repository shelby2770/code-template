/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Basic Trie (Prefix Tree) implementation for string storage and retrieval.
 * Supports insertion, search, and prefix matching operations.
 * Time: O(L) per operation where L is the length of the string
 * Usage: Insert strings, check prefixes, search for complete words
 */
#pragma once

struct trie {
  int sz = 0;
  trie *nxt[26];
};

trie root = trie();
trie *now = &root;
