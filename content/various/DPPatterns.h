/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Comprehensive Dynamic Programming Problem Types and Patterns.
 * Time: 
 * Usage: 
 */
#pragma once

/*
COMPREHENSIVE DYNAMIC PROGRAMMING PATTERNS WITH CODE

1. KNAPSACK VARIATIONS:
*/

// a) 0/1 Knapsack: dp[i][w] = max value using first i items with weight <= w
// Time: O(n*W), Space: O(n*W)
int knapsack01(vector<int>& weights, vector<int>& values, int W) {
  int n = weights.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= W; w++) {
      dp[i][w] = dp[i-1][w]; // don't take item i-1
      if (weights[i-1] <= w) {
        dp[i][w] = max(dp[i][w], dp[i-1][w-weights[i-1]] + values[i-1]);
      }
    }
  }
  return dp[n][W];
}

// b) Unbounded Knapsack: unlimited items, dp[w] = max value with weight <= w
// Time: O(n*W), Space: O(W)
int unboundedKnapsack(vector<int>& weights, vector<int>& values, int W) {
  vector<int> dp(W + 1, 0);
  for (int w = 1; w <= W; w++) {
    for (int i = 0; i < weights.size(); i++) {
      if (weights[i] <= w) {
        dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
      }
    }
  }
  return dp[W];
}

// c) Bounded Knapsack: each item has limited copies, uses binary splitting
// Time: O(W * sum(log counts)), Space: O(W)
int boundedKnapsack(vector<int>& weights, vector<int>& values, vector<int>& counts, int W) {
  vector<int> dp(W + 1, 0);
  
  for (int i = 0; i < weights.size(); i++) {
    for (int k = 1; k <= counts[i]; k *= 2) {
      int take = min(k, counts[i]);
      int w = weights[i] * take;
      int v = values[i] * take;
      
      for (int j = W; j >= w; j--) {
        dp[j] = max(dp[j], dp[j - w] + v);
      }
      counts[i] -= take;
    }
  }
  return dp[W];
}

// d) Subset Sum (Boolean): dp[s] = true if sum s is achievable
// Time: O(n*target), Space: O(target)
bool subsetSum(vector<int>& nums, int target) {
  vector<bool> dp(target + 1, false);
  dp[0] = true;
  
  for (int num : nums) {
    for (int j = target; j >= num; j--) {
      dp[j] = dp[j] || dp[j - num];
    }
  }
  return dp[target];
}

// e) Subset Sum with Bitset: ultra-fast using bitshift operations
// Time: O(n*target/64), Space: O(target)
bool subsetSumBitset(vector<int>& nums, int target) {
  bitset<100001> bs;
  bs[0] = 1;
  for (int num : nums) {
    bs |= (bs << num);
  }
  return bs[target];
}

// f) Partition Equal Subset Sum: can split array into two equal-sum parts
// Time: O(n*sum), Space: O(sum)
bool canPartition(vector<int>& nums) {
  int sum = 0;
  for (int num : nums) sum += num;
  if (sum % 2 == 1) return false;
  return subsetSum(nums, sum / 2);
}

// g) Value-Optimized Knapsack: when W is large but sum of values is small
// Time: O(n*sum_values), Space: O(sum_values)
int valueOptimizedKnapsack(vector<int>& weights, vector<int>& values, int W) {
  int maxValue = 0;
  for (int v : values) maxValue += v;
  
  vector<int> dp(maxValue + 1, INT_MAX);
  dp[0] = 0;
  
  for (int i = 0; i < weights.size(); i++) {
    for (int v = maxValue; v >= values[i]; v--) {
      if (dp[v - values[i]] != INT_MAX) {
        dp[v] = min(dp[v], dp[v - values[i]] + weights[i]);
      }
    }
  }
  
  for (int v = maxValue; v >= 0; v--) {
    if (dp[v] <= W) return v;
  }
  return 0;
}

// h) Meet-in-the-Middle Knapsack: exponential split for n~40
// Time: O(2^(n/2) * log(2^(n/2))), Space: O(2^(n/2))
int meetInMiddleKnapsack(vector<int>& weights, vector<int>& values, int W) {
  int n = weights.size();
  int n1 = n / 2, n2 = n - n1;
  
  // Generate all possible sums for first half
  vector<pair<int, int>> first; // {weight, value}
  for (int mask = 0; mask < (1 << n1); mask++) {
    int w = 0, v = 0;
    for (int i = 0; i < n1; i++) {
      if (mask & (1 << i)) {
        w += weights[i];
        v += values[i];
      }
    }
    if (w <= W) first.push_back({w, v});
  }
  
  // Sort by weight and keep only pareto optimal (max value for each weight)
  sort(first.begin(), first.end());
  vector<pair<int, int>> optimal;
  int maxVal = 0;
  for (auto& p : first) {
    if (p.second > maxVal) {
      maxVal = p.second;
      optimal.push_back(p);
    }
  }
  
  int result = 0;
  // Generate all possible sums for second half
  for (int mask = 0; mask < (1 << n2); mask++) {
    int w2 = 0, v2 = 0;
    for (int i = 0; i < n2; i++) {
      if (mask & (1 << i)) {
        w2 += weights[n1 + i];
        v2 += values[n1 + i];
      }
    }
    if (w2 <= W) {
      // Binary search for best match from first half
      int remaining = W - w2;
      auto it = upper_bound(optimal.begin(), optimal.end(), 
                           make_pair(remaining, INT_MAX));
      if (it != optimal.begin()) {
        --it;
        result = max(result, v2 + it->second);
      }
    }
  }
  return result;
}

/*
2. COIN CHANGE VARIATIONS:
*/

// a) Min Coins: dp[amount] = min coins to make amount
// Time: O(n*amount), Space: O(amount)
int coinChange(vector<int>& coins, int amount) {
  vector<int> dp(amount + 1, INT_MAX);
  dp[0] = 0;
  for (int coin : coins) {
    for (int i = coin; i <= amount; i++) {
      if (dp[i - coin] != INT_MAX) {
        dp[i] = min(dp[i], dp[i - coin] + 1);
      }
    }
  }
  return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// b) Coin Combinations: dp[amount] = ways to make amount (order doesn't matter)
// Time: O(n*amount), Space: O(amount)
int coinCombinations(vector<int>& coins, int amount) {
  vector<int> dp(amount + 1, 0);
  dp[0] = 1;
  for (int coin : coins) {          // COIN OUTER -> combinations
    for (int i = coin; i <= amount; i++) {
      dp[i] += dp[i - coin];
    }
  }
  return dp[amount];
}

// c) Coin Permutations: dp[amount] = ways to make amount (order matters)
// Time: O(n*amount), Space: O(amount)
int coinPermutations(vector<int>& coins, int amount) {
  vector<int> dp(amount + 1, 0);
  dp[0] = 1;
  for (int i = 1; i <= amount; i++) {    // AMOUNT OUTER -> permutations
    for (int coin : coins) {
      if (coin <= i) {
        dp[i] += dp[i - coin];
      }
    }
  }
  return dp[amount];
}

// d) Bounded Coin Change: each coin type has limited quantity
// Time: O(amount * sum(log counts)), Space: O(amount)
int boundedCoinChange(vector<int>& coins, vector<int>& counts, int amount) {
  vector<int> dp(amount + 1, 0);
  dp[0] = 1;
  
  for (int i = 0; i < coins.size(); i++) {
    int coin = coins[i];
    int count = counts[i];
    
    // Binary splitting for efficiency
    for (int k = 1; k <= count; k *= 2) {
      int use = min(k, count);
      int value = coin * use;
      
      for (int j = amount; j >= value; j--) {
        dp[j] += dp[j - value];
      }
      count -= use;
    }
    
    if (count > 0) {
      int value = coin * count;
      for (int j = amount; j >= value; j--) {
        dp[j] += dp[j - value];
      }
    }
  }
  return dp[amount];
}

// e) Count subsets with exact sum: dp[s] = count of subsets with sum s
// Time: O(n*target), Space: O(target)
int countSubsetsWithSum(vector<int>& nums, int target, int mod) {
  vector<int> dp(target + 1, 0);
  dp[0] = 1;
  
  for (int num : nums) {
    for (int j = target; j >= num; j--) {
      dp[j] = (dp[j] + dp[j - num]) % mod;
    }
  }
  return dp[target];
}

/*
SPECIALIZED KNAPSACK VARIANTS:
*/

// Tree Knapsack: items have parent-child dependency
class TreeKnapsack {
  struct Node {
    int weight, value;
    vector<int> children;
  };
  
  vector<Node> tree;
  
  vector<int> dfs(int node, int W) {
    vector<int> dp(W + 1, 0);
    
    // If we take this node
    if (tree[node].weight <= W) {
      vector<int> combined(W - tree[node].weight + 1, tree[node].value);
      
      for (int child : tree[node].children) {
        vector<int> childDP = dfs(child, W - tree[node].weight);
        vector<int> newCombined(W - tree[node].weight + 1, 0);
        
        // Merge knapsack
        for (int i = 0; i <= W - tree[node].weight; i++) {
          for (int j = 0; j <= W - tree[node].weight - i; j++) {
            newCombined[i + j] = max(newCombined[i + j], combined[i] + childDP[j]);
          }
        }
        combined = newCombined;
      }
      
      for (int i = tree[node].weight; i <= W; i++) {
        dp[i] = max(dp[i], combined[i - tree[node].weight]);
      }
    }
    
    // Don't take this node (but can take subtrees)
    for (int child : tree[node].children) {
      vector<int> childDP = dfs(child, W);
      for (int i = 0; i <= W; i++) {
        dp[i] = max(dp[i], childDP[i]);
      }
    }
    
    return dp;
  }
  
public:
  int solve(int root, int W) {
    vector<int> result = dfs(root, W);
    return result[W];
  }
};

// 2D Knapsack: two constraints (weight and volume)
int knapsack2D(vector<int>& weights, vector<int>& volumes, vector<int>& values, int W, int V) {
  vector<vector<int>> dp(W + 1, vector<int>(V + 1, 0));
  
  for (int i = 0; i < weights.size(); i++) {
    for (int w = W; w >= weights[i]; w--) {
      for (int v = V; v >= volumes[i]; v--) {
        dp[w][v] = max(dp[w][v], dp[w - weights[i]][v - volumes[i]] + values[i]);
      }
    }
  }
  return dp[W][V];
}

// Knapsack with item dependencies (general DAG)
int knapsackDAG(vector<int>& weights, vector<int>& values, vector<vector<int>>& prereq, int W) {
  int n = weights.size();
  vector<int> indegree(n, 0);
  vector<vector<int>> adj(n);
  
  for (int i = 0; i < n; i++) {
    for (int dep : prereq[i]) {
      adj[dep].push_back(i);
      indegree[i]++;
    }
  }
  
  // Topological sort
  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (indegree[i] == 0) q.push(i);
  }
  
  vector<int> topo;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    topo.push_back(u);
    for (int v : adj[u]) {
      if (--indegree[v] == 0) {
        q.push(v);
      }
    }
  }
  
  // DP in topological order
  vector<vector<int>> dp(n, vector<int>(W + 1, 0));
  
  for (int item : topo) {
    for (int w = 0; w <= W; w++) {
      // Don't take item
      dp[item][w] = 0;
      for (int dep : prereq[item]) {
        dp[item][w] = max(dp[item][w], dp[dep][w]);
      }
      
      // Take item (if weight allows and all prerequisites satisfied)
      if (w >= weights[item]) {
        int minFromDeps = 0;
        for (int dep : prereq[item]) {
          minFromDeps = max(minFromDeps, dp[dep][w - weights[item]]);
        }
        dp[item][w] = max(dp[item][w], minFromDeps + values[item]);
      }
    }
  }
  
  int result = 0;
  for (int i = 0; i < n; i++) {
    result = max(result, dp[i][W]);
  }
  return result;
}

/*
KNAPSACK TEMPLATES & MISTAKE PREVENTION:
*/

// Clean 0/1 Knapsack (competitive style): dp[w] = max value with weight <= w
// Time: O(n*W), Space: O(W)
int knapsack01Clean(int n, int W, vector<int>& wt, vector<int>& val) {
  vector<int> dp(W + 1, 0);
  for (int i = 0; i < n; ++i) {
    for (int w = W; w >= wt[i]; --w) {    // REVERSE for 0/1
      dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    }
  }
  return dp[W];
}

// Unbounded/Coin Change clean template: dp[amount] = ways to make amount
// Time: O(n*amount), Space: O(amount)  
int coinChangeCount(vector<int>& coins, int amount) {
  vector<int> dp(amount + 1, 0);
  dp[0] = 1;
  for (int coin : coins) {              // coin outer -> combinations
    for (int x = coin; x <= amount; ++x) {    // FORWARD for unbounded
      dp[x] += dp[x - coin];
    }
  }
  return dp[amount];
}

// Min coins template: dp[amount] = minimum coins needed for amount
// Time: O(n*amount), Space: O(amount)
int minCoins(vector<int>& coins, int amount) {
  const int INF = 1e9;
  vector<int> dp(amount + 1, INF);
  dp[0] = 0;
  for (int coin : coins) {
    for (int x = coin; x <= amount; ++x) {
      dp[x] = min(dp[x], dp[x - coin] + 1);
    }
  }
  return dp[amount] >= INF ? -1 : dp[amount];
}

/*
CRITICAL REMINDERS:
0/1 knapsack: REVERSE loop (prevents reuse)
Unbounded: FORWARD loop (allows reuse)  
Combinations: coin outer, Permutations: amount outer
Always dp[0] = 0 for max/min, dp[0] = 1 for counting
*/

/*
3. LONGEST COMMON SUBSEQUENCE (LCS):
*/

// a) Standard LCS: dp[i][j] = LCS length of first i chars of s1, first j chars of s2
// Time: O(m*n), Space: O(m*n)
int LCS(string s1, string s2) {
  int m = s1.length(), n = s2.length();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s1[i-1] == s2[j-1]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }
  return dp[m][n];
}

// d) Edit Distance (Levenshtein): min operations to transform s1 to s2
// Time: O(m*n), Space: O(m*n)
int editDistance(string s1, string s2) {
  int m = s1.length(), n = s2.length();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));
  for (int i = 0; i <= m; i++) dp[i][0] = i;
  for (int j = 0; j <= n; j++) dp[0][j] = j;
  
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s1[i-1] == s2[j-1]) {
        dp[i][j] = dp[i-1][j-1];
      } else {
        dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
      }
    }
  }
  return dp[m][n];
}

/*
4. LONGEST INCREASING SUBSEQUENCE (LIS):
*/

// a) Standard LIS: dp[i] = length of LIS ending at position i
// Time: O(n^2), Space: O(n)
int LIS(vector<int>& nums) {
  int n = nums.size();
  vector<int> dp(n, 1);
  int maxLen = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[j] < nums[i]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    maxLen = max(maxLen, dp[i]);
  }
  return maxLen;
}

// b) LIS using binary search: maintains array of smallest tail for each length
// Time: O(n log n), Space: O(n)
int LIS_fast(vector<int>& nums) {
  vector<int> lis;
  for (int num : nums) {
    auto it = lower_bound(lis.begin(), lis.end(), num);
    if (it == lis.end()) {
      lis.push_back(num);
    } else {
      *it = num;
    }
  }
  return lis.size();
}

/*
5. PATH PROBLEMS:
*/

// a) Unique Paths: dp[i][j] = number of ways to reach position (i,j)
// Time: O(m*n), Space: O(m*n)
int uniquePaths(int m, int n) {
  vector<vector<int>> dp(m, vector<int>(n, 1));
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      dp[i][j] = dp[i-1][j] + dp[i][j-1];
    }
  }
  return dp[m-1][n-1];
}

// b) Min Path Sum: dp[i][j] = minimum sum to reach position (i,j)
// Time: O(m*n), Space: O(m*n)
int minPathSum(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  vector<vector<int>> dp(m, vector<int>(n));
  dp[0][0] = grid[0][0];
  
  for (int i = 1; i < m; i++) dp[i][0] = dp[i-1][0] + grid[i][0];
  for (int j = 1; j < n; j++) dp[0][j] = dp[0][j-1] + grid[0][j];
  
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
    }
  }
  return dp[m-1][n-1];
}

/*
6. SUBSTRING/SUBARRAY PROBLEMS:
*/

// a) Max Subarray Sum (Kadane's): tracks current and maximum sum ending at each position
// Time: O(n), Space: O(1)
int maxSubArray(vector<int>& nums) {
  int maxSum = nums[0], currentSum = nums[0];
  for (int i = 1; i < nums.size(); i++) {
    currentSum = max(nums[i], currentSum + nums[i]);
    maxSum = max(maxSum, currentSum);
  }
  return maxSum;
}

// b) Max Product Subarray: tracks both max and min product ending at each position
// Time: O(n), Space: O(1)
int maxProduct(vector<int>& nums) {
  int maxProd = nums[0], minProd = nums[0], result = nums[0];
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] < 0) swap(maxProd, minProd);
    maxProd = max(nums[i], maxProd * nums[i]);
    minProd = min(nums[i], minProd * nums[i]);
    result = max(result, maxProd);
  }
  return result;
}

// c) Longest Palindromic Substring: dp[i][j] = true if substring s[i..j] is palindrome
// Time: O(n^2), Space: O(n^2)
string longestPalindrome(string s) {
  int n = s.length();
  vector<vector<bool>> dp(n, vector<bool>(n, false));
  int start = 0, maxLen = 1;
  
  // All single characters are palindromes
  for (int i = 0; i < n; i++) dp[i][i] = true;
  
  // Check for palindromes of length 2
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == s[i + 1]) {
      dp[i][i + 1] = true;
      start = i;
      maxLen = 2;
    }
  }
  
  // Check for palindromes of length 3 and more
  for (int len = 3; len <= n; len++) {
    for (int i = 0; i < n - len + 1; i++) {
      int j = i + len - 1;
      if (s[i] == s[j] && dp[i + 1][j - 1]) {
        dp[i][j] = true;
        start = i;
        maxLen = len;
      }
    }
  }
  return s.substr(start, maxLen);
}

/*
7. TREE DP EXAMPLES:
*/

// Tree Diameter using DFS
class TreeDP {
  vector<vector<int>> adj;
  int maxDist = 0;
  
  int dfs(int node, int parent) {
    int max1 = 0, max2 = 0;
    for (int child : adj[node]) {
      if (child != parent) {
        int depth = dfs(child, node);
        if (depth > max1) {
          max2 = max1;
          max1 = depth;
        } else if (depth > max2) {
          max2 = depth;
        }
      }
    }
    maxDist = max(maxDist, max1 + max2);
    return max1 + 1;
  }
  
public:
  int treeDiameter(int n, vector<vector<int>>& edges) {
    adj.resize(n);
    for (auto& edge : edges) {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }
    dfs(0, -1);
    return maxDist;
  }
};

/*
8. GAME THEORY DP:
*/

// Stone Game - optimal play: dp[i][j] = score difference for player 1 in range [i,j]
// Time: O(n^2), Space: O(n^2)
bool stoneGame(vector<int>& piles) {
  int n = piles.size();
  vector<vector<int>> dp(n, vector<int>(n, 0));
  
  for (int i = 0; i < n; i++) dp[i][i] = piles[i];
  
  for (int len = 2; len <= n; len++) {
    for (int i = 0; i <= n - len; i++) {
      int j = i + len - 1;
      dp[i][j] = max(piles[i] - dp[i+1][j], piles[j] - dp[i][j-1]);
    }
  }
  return dp[0][n-1] > 0;
}

/*
9. INTERVAL DP:
*/

// Matrix Chain Multiplication: dp[i][j] = min cost to multiply matrices i to j
// Time: O(n^3), Space: O(n^2)
int matrixChainMultiplication(vector<int>& dims) {
  int n = dims.size() - 1;
  vector<vector<int>> dp(n, vector<int>(n, 0));
  
  for (int len = 2; len <= n; len++) {
    for (int i = 0; i <= n - len; i++) {
      int j = i + len - 1;
      dp[i][j] = INT_MAX;
      for (int k = i; k < j; k++) {
        int cost = dp[i][k] + dp[k+1][j] + dims[i] * dims[k+1] * dims[j+1];
        dp[i][j] = min(dp[i][j], cost);
      }
    }
  }
  return dp[0][n-1];
}

/*
10. DIGIT DP:
*/

// Count numbers with digit sum equal to target: digit DP with tight bound
// Time: O(n * target * 2), Space: O(n * target * 2)
int digitDP(string num, int target) {
  int n = num.length();
  vector<vector<vector<int>>> memo(n, vector<vector<int>>(target + 1, vector<int>(2, -1)));
  
  function<int(int, int, bool)> solve = [&](int pos, int sum, bool tight) -> int {
    if (pos == n) return sum == target ? 1 : 0;
    if (memo[pos][sum][tight] != -1) return memo[pos][sum][tight];
    
    int limit = tight ? (num[pos] - '0') : 9;
    int result = 0;
    
    for (int digit = 0; digit <= limit; digit++) {
      if (sum + digit <= target) {
        result += solve(pos + 1, sum + digit, tight && (digit == limit));
      }
    }
    return memo[pos][sum][tight] = result;
  };
  
  return solve(0, 0, true);
}

/*
11. BITMASK DP:
*/

// Traveling Salesman Problem: dp[mask][i] = min cost visiting cities in mask, ending at i
// Time: O(n^2 * 2^n), Space: O(n * 2^n)
int TSP(vector<vector<int>>& dist) {
  int n = dist.size();
  vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
  dp[1][0] = 0; // Start from city 0
  
  for (int mask = 1; mask < (1 << n); mask++) {
    for (int u = 0; u < n; u++) {
      if (!(mask & (1 << u)) || dp[mask][u] == INT_MAX) continue;
      for (int v = 0; v < n; v++) {
        if (mask & (1 << v)) continue;
        int newMask = mask | (1 << v);
        dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + dist[u][v]);
      }
    }
  }
  
  int result = INT_MAX;
  for (int i = 1; i < n; i++) {
    result = min(result, dp[(1 << n) - 1][i] + dist[i][0]);
  }
  return result;
}

/*
12. STATE MACHINE DP:
*/

// Stock Trading with Cooldown: state machine DP with buy/sell/rest states
// Time: O(n), Space: O(n)
int stockWithCooldown(vector<int>& prices) {
  int n = prices.size();
  if (n <= 1) return 0;
  
  vector<int> buy(n), sell(n), rest(n);
  buy[0] = -prices[0];
  sell[0] = 0;
  rest[0] = 0;
  
  for (int i = 1; i < n; i++) {
    buy[i] = max(buy[i-1], rest[i-1] - prices[i]);
    sell[i] = max(sell[i-1], buy[i-1] + prices[i]);
    rest[i] = max(rest[i-1], sell[i-1]);
  }
  return sell[n-1];
}

// House Robber: dp[i] = max money robbed from houses 0 to i
// Time: O(n), Space: O(n)
int rob(vector<int>& nums) {
  int n = nums.size();
  if (n == 0) return 0;
  if (n == 1) return nums[0];
  
  vector<int> dp(n);
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);
  
  for (int i = 2; i < n; i++) {
    dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
  }
  return dp[n-1];
}

/*
SPACE OPTIMIZATIONS:
*/

// 0/1 Knapsack with O(W) space: space-optimized version using 1D array
// Time: O(n*W), Space: O(W)
int knapsack01Optimized(vector<int>& weights, vector<int>& values, int W) {
  vector<int> dp(W + 1, 0);
  for (int i = 0; i < weights.size(); i++) {
    for (int w = W; w >= weights[i]; w--) {
      dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
    }
  }
  return dp[W];
}


/*
COMPLEXITY REFERENCE:
- 1D DP: O(n) states, usually O(n) or O(n^2) time
- 2D DP: O(n^2) states, usually O(n^2) or O(n^3) time  
- Tree DP: O(n) states, O(n) time for each node
- Bitmask DP: O(2^n * n) states for TSP-like problems
- Digit DP: O(log n * sum * tight) states
*/

/*
ADVANCED DP OPTIMIZATIONS:
*/

/*
13. CONVEX HULL TRICK (CHT):
For DP transitions of form: dp[i] = min(dp[j] + cost(j, i)) where cost has convex property
Optimizes from O(n^2) to O(n log n) or O(n) with monotonic queries
*/

struct Line {
  long long m, b; // y = mx + b
  long long eval(long long x) { return m * x + b; }
  long double intersectX(Line l) { return (long double)(l.b - b) / (m - l.m); }
};

class ConvexHullTrick {
  vector<Line> lines;
  int ptr = 0;
  
  bool bad(Line l1, Line l2, Line l3) {
    return l1.intersectX(l3) <= l1.intersectX(l2);
  }
  
public:
  void addLine(long long m, long long b) {
    Line newLine = {m, b};
    while (lines.size() >= 2 && bad(lines[lines.size()-2], lines[lines.size()-1], newLine)) {
      lines.pop_back();
    }
    lines.push_back(newLine);
  }
  
  long long query(long long x) {
    if (lines.empty()) return LLONG_MAX;
    ptr = min(ptr, (int)lines.size() - 1);
    while (ptr < lines.size() - 1 && lines[ptr].eval(x) >= lines[ptr + 1].eval(x)) {
      ptr++;
    }
    return lines[ptr].eval(x);
  }
};

// Example: Building optimization DP using CHT for quadratic cost transitions  
// Time: O(n), Space: O(n)
long long buildingOptimization(vector<long long>& cost) {
  int n = cost.size();
  vector<long long> dp(n + 1, LLONG_MAX);
  vector<long long> prefix(n + 1, 0);
  
  for (int i = 1; i <= n; i++) {
    prefix[i] = prefix[i-1] + cost[i-1];
  }
  
  ConvexHullTrick cht;
  dp[0] = 0;
  cht.addLine(0, 0);
  
  for (int i = 1; i <= n; i++) {
    dp[i] = cht.query(prefix[i]);
    cht.addLine(-prefix[i], dp[i] + prefix[i] * prefix[i]);
  }
  return dp[n];
}

/*
14. KNUTH-YAO OPTIMIZATION:
For DP of form: dp[i][j] = min(dp[i][k] + dp[k+1][j] + cost[i][j]) where cost satisfies quadrangle inequality
Reduces complexity from O(n^3) to O(n^2)
*/

// Matrix Chain Multiplication with Knuth optimization: uses quadrangle inequality
// Time: O(n^2), Space: O(n^2)
int matrixChainKnuth(vector<int>& dims) {
  int n = dims.size() - 1;
  vector<vector<int>> dp(n, vector<int>(n, 0));
  vector<vector<int>> opt(n, vector<int>(n, 0));
  
  // Initialize opt for length 1
  for (int i = 0; i < n; i++) opt[i][i] = i;
  
  for (int len = 2; len <= n; len++) {
    for (int i = 0; i <= n - len; i++) {
      int j = i + len - 1;
      dp[i][j] = INT_MAX;
      
      int start = (i == 0) ? 0 : opt[i][j-1];
      int end = (j == n-1) ? j-1 : opt[i+1][j];
      
      for (int k = start; k <= end; k++) {
        int cost = dp[i][k] + dp[k+1][j] + dims[i] * dims[k+1] * dims[j+1];
        if (cost < dp[i][j]) {
          dp[i][j] = cost;
          opt[i][j] = k;
        }
      }
    }
  }
  return dp[0][n-1];
}

/*
15. DIVIDE AND CONQUER OPTIMIZATION:
For DP where optimal k is monotonic: if opt[i][j] <= opt[i][j+1]
Reduces from O(kn^2) to O(kn log n)
*/

void divideConquerDP(int l, int r, int optL, int optR, vector<vector<long long>>& dp, 
                     vector<vector<long long>>& cost, int layer) {
  if (l > r) return;
  
  int mid = (l + r) / 2;
  pair<long long, int> best = {LLONG_MAX, -1};
  
  for (int k = optL; k <= min(mid, optR); k++) {
    long long val = dp[layer-1][k] + cost[k][mid];
    best = min(best, {val, k});
  }
  
  dp[layer][mid] = best.first;
  int opt = best.second;
  
  divideConquerDP(l, mid - 1, optL, opt, dp, cost, layer);
  divideConquerDP(mid + 1, r, opt, optR, dp, cost, layer);
}

/*
16. SUM OVER SUBSETS (SOS) DP:
Calculate sum of f(S) for all subsets S of given set
Time: O(n * 2^n) instead of O(3^n) brute force
*/

// SUM OVER SUBSETS (SOS) DP: calculate f(S) for all subsets S efficiently
// Time: O(n * 2^n), Space: O(2^n)
vector<long long> sumOverSubsets(vector<long long>& arr) {
  int n = __builtin_ctz(arr.size()); // log2 of size
  vector<long long> dp = arr;
  
  for (int i = 0; i < n; i++) {
    for (int mask = 0; mask < (1 << n); mask++) {
      if (mask & (1 << i)) {
        dp[mask] += dp[mask ^ (1 << i)];
      }
    }
  }
  return dp;
}

// SOS DP variant: Count subsets with XOR = 0 using frequency array
// Time: O(maxVal * maxVal), Space: O(maxVal)
int countXORZeroSubsets(vector<int>& nums) {
  int maxXOR = 0;
  for (int x : nums) maxXOR = max(maxXOR, x);
  
  vector<int> cnt(maxXOR + 1, 0);
  for (int x : nums) cnt[x]++;
  
  vector<long long> dp(maxXOR + 1, 0);
  dp[0] = 1;
  
  for (int i = 0; i <= maxXOR; i++) {
    if (cnt[i] > 0) {
      vector<long long> newDp = dp;
      for (int mask = 0; mask <= maxXOR; mask++) {
        newDp[mask ^ i] += dp[mask] * cnt[i];
      }
      dp = newDp;
    }
  }
  return dp[0] - 1; // Subtract empty set
}

/*
17. SLOPE TRICK:
Maintain piecewise linear function for optimization problems
Useful for problems with "buy low, sell high" patterns
*/

class SlopeTrick {
  priority_queue<long long> L; // max heap for left slopes
  priority_queue<long long, vector<long long>, greater<long long>> R; // min heap for right
  long long minVal = 0;
  long long lazyL = 0, lazyR = 0;
  
public:
  void addRamp(long long a) { // add max(0, x - a)
    if (L.empty() || a <= L.top() + lazyL) {
      L.push(a - lazyL);
    } else if (R.empty() || a >= R.top() + lazyR) {
      R.push(a - lazyR);
    } else {
      minVal += a - (R.top() + lazyR);
      L.push(R.top() + lazyR - lazyL);
      R.pop();
      R.push(a - lazyR);
    }
  }
  
  void shiftRight(long long d) { lazyR += d; }
  void shiftLeft(long long d) { lazyL += d; }
  
  long long getMin() { return minVal; }
};

/*
18. ALIENS TRICK (Lagrange Multipliers):
Convert constrained optimization to unconstrained using binary search on penalty
*/

pair<long long, int> aliensTrick(vector<long long>& cost, int k, long long penalty) {
  int n = cost.size();
  vector<long long> dp(n + 1, LLONG_MIN);
  vector<int> cnt(n + 1, 0);
  
  dp[0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      long long val = dp[j] + cost[i-1] - penalty;
      if (val > dp[i]) {
        dp[i] = val;
        cnt[i] = cnt[j] + 1;
      }
    }
  }
  return {dp[n], cnt[n]};
}

/*
19. BROKEN PROFILE DP (Tiling DP):
DP on grid with bitmask representing filled cells
*/

// DP on grid with bitmask: dp[col][mask] = ways to tile up to column col
// Time: O(m * 2^n * n), Space: O(2^n)
int tilingDP(int n, int m) {
  vector<vector<int>> dp(m, vector<int>(1 << n, 0));
  dp[0][0] = 1;
  
  for (int col = 0; col < m; col++) {
    for (int mask = 0; mask < (1 << n); mask++) {
      if (dp[col][mask] == 0) continue;
      
      function<void(int, int, int)> generate = [&](int pos, int cur, int next) {
        if (pos == n) {
          if (col + 1 < m) dp[col + 1][next] += dp[col][cur];
          return;
        }
        
        if (cur & (1 << pos)) {
          generate(pos + 1, cur, next);
        } else {
          generate(pos + 1, cur | (1 << pos), next | (1 << pos)); // vertical tile
          if (pos + 1 < n && !(cur & (1 << (pos + 1)))) {
            generate(pos + 2, cur | (1 << pos) | (1 << (pos + 1)), next); // horizontal tile
          }
        }
      };
      
      generate(0, mask, 0);
    }
  }
  return dp[m-1][0];
}

/*
COMPLEXITY REFERENCE FOR ADVANCED TECHNIQUES:
- Convex Hull Trick: O(n log n) or O(n) with monotonic queries
- Knuth-Yao: O(n^2) instead of O(n^3)
- Divide & Conquer: O(kn log n) instead of O(kn^2)
- SOS DP: O(n * 2^n) instead of O(3^n)
- Slope Trick: O(n log n) with priority queues
- Aliens Trick: O(n^2 log V) where V is value range
- Broken Profile: O(m * 2^n * n) for nxm grid
*/
