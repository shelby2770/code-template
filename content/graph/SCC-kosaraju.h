/**
 * Author: User
 * Date: 2025-09-18
 * License: CC0
 * Source: 
 * Description: Kosaraju's algorithm for finding strongly connected components.
 * Step 1: Perform DFS on original graph, record finishing order.
 * Step 2: Create transpose graph (reverse all edges).
 * Step 3: Perform DFS on transpose graph in reverse finishing order.
 * Each DFS tree in step 3 is one strongly connected component.
 * Time: O(V+E)
 * Status: Tested
 */