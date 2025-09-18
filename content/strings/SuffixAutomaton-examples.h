/**
 * Example usage of Suffix Automaton
 */

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  string s;
  cin >> s;
  
  SuffixAutomaton sa(s.size());
  sa.build(s);
  
  // Count unique substrings
  cout << "Number of unique substrings: " << sa.countUniqueSubstrings() << '\n';
  
  // Check if a pattern exists
  string pattern = "abc";
  cout << "Pattern " << pattern << " exists: " << (sa.exists(pattern) ? "Yes" : "No") << '\n';
  
  // Find first occurrence
  cout << "First occurrence of " << pattern << " ends at position: " << sa.findFirstOccurrence(pattern) << '\n';
  
  // Count occurrences
  cout << "Number of occurrences of " << pattern << ": " << sa.countOccurrences(pattern) << '\n';
  
  // Find longest common substring with another string
  string s2 = "xabcyz";
  cout << "Longest common substring with " << s2 << ": " << sa.longestCommonSubstring(s2) << '\n';
  
  return 0;
} 