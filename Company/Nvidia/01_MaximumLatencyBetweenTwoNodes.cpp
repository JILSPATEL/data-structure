/*
Problem 1: Maximum Latency Between Two Nodes
Pattern: Weighted Tree Diameter

1. Understand the Problem:
   - We are given a tree with N nodes and N-1 weighted edges.
   - Each edge has a weight representing the latency between two nodes.
   - We need to find the maximum total latency between any two nodes.
   - The latency of a path is the sum of all edge weights along that path.

   Example:
       1 --3-- 2 --4-- 3
               |
               2
               |
               4 --6-- 5

   Path from node 3 to node 5:
       3 -> 2 -> 4 -> 5

   Total latency = 4 + 2 + 6 = 12
   Answer = 12

2. Brute Force Approach:
   - Start DFS from every node.
   - Calculate distances to all other nodes.
   - Keep track of the maximum distance.
   - Time Complexity: O(N^2).

3. Optimized Approach: Two-Traversal Tree Diameter

   Step 1:
   - Start DFS/BFS from any node, say node 1.
   - Find the farthest node from node 1.
   - Suppose the farthest node is node A.

   Step 2:
   - Start another DFS/BFS from node A.
   - Calculate distances to all other nodes.
   - Find the maximum distance.
   - This maximum distance is the tree diameter.

   Step 3:
   - Return the maximum distance obtained in Step 2.

4. Example Walkthrough:
   - First traversal from node 1 finds node 5 as the farthest node.
   - Second traversal from node 5 finds node 3 as the farthest node.
   - Distance from node 5 to node 3 = 6 + 2 + 4 = 12.
   - Therefore, the answer is 12.

5. Why Does This Work?
   - The diameter is the longest path between any two nodes in a tree.
   - The first traversal finds an endpoint of a diameter.
   - The second traversal finds the opposite endpoint and calculates
     the diameter.
   - Since a tree has exactly one path between any two nodes, we do
     not need Dijkstra's algorithm.
   - This technique works when all edge weights are non-negative.

6. Complexity Analysis:
   - Time Complexity: O(N), because we traverse the tree twice.
   - Space Complexity: O(N), for the adjacency list and traversal data.

7. Interview Recognition:
   - Whenever a problem asks for the longest path between any two
     nodes in a weighted tree, consider the tree diameter technique.
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using pp = pair<int, int>;

    pair<int, long long> dfs(
        int node,
        int parent,
        long long dist,
        vector<vector<pp>>& adj
    ) {
        pair<int, long long> farthest = {node, dist};

        for (auto edge : adj[node]) {
            int child = edge.first;
            int wt = edge.second;

            if (child == parent) continue;

            auto result = dfs(child, node, dist + wt, adj);

            if (result.second > farthest.second) {
                farthest = result;
            }
        }

        return farthest;
    }

    long long treeDiameter(int n, vector<vector<int>>& edges) {
        vector<vector<pp>> adj(n + 1);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        auto first = dfs(1, -1, 0, adj);
        int farthestNode = first.first;

        auto second = dfs(farthestNode, -1, 0, adj);

        return second.second;
    }
};

int main() {
    int N = 5;

    vector<vector<int>> edges = {
        {1, 2, 3},
        {2, 3, 4},
        {2, 4, 2},
        {4, 5, 6}
    };

    Solution sol;
    cout << sol.treeDiameter(N, edges) << endl;

    return 0;
}
