/**
 * Problem: Detect Cycle in an Undirected Graph using DFS
 *
 * Approach:
 * 1. Convert edge list into adjacency list.
 * 2. Use DFS traversal.
 * 3. Maintain:
 *      - visited array
 *      - parent node
 * 4. If a visited neighbour is found that is NOT the parent,
 *    then cycle exists.
 *
 * Example 1:
 * V = 5, E = 5
 * Edges: (0,1), (0,2), (1,2), (2,3), (3,4)
 * Output: true
 * Explanation: Cycle exists: 0-1-2-0
 *
 * Example 2:
 * V = 4, E = 3
 * Edges: (0,1), (0,2), (1,3)
 * Output: false
 * Explanation: No cycle, it's a tree structure
 *
 * Example 3:
 * V = 3, E = 3
 * Edges: (0,1), (1,2), (2,0)
 * Output: true
 * Explanation: Triangle cycle: 0-1-2-0
 *
 * Time Complexity:
 * O(V + E)
 *
 * Space Complexity:
 * O(V + E)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool dfs(vector<vector<int>>& adj,
             int node,
             int parent,
             vector<int>& vis) {

        vis[node] = 1;

        for (auto &neigh : adj[node]) {

            // If neighbour is not visited
            if (!vis[neigh]) {

                if (dfs(adj, neigh, node, vis)) {
                    return true;
                }
            }

            // If visited neighbour is not parent
            else if (neigh != parent) {
                return true;
            }
        }

        return false;
    }

    bool isCycle(int V, vector<vector<int>>& edges) {

        // Adjacency List
        vector<vector<int>> adj(V);

        for (auto &edge : edges) {

            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Visited Array
        vector<int> vis(V, 0);

        // Check every component
        for (int i = 0; i < V; i++) {

            if (!vis[i]) {

                if (dfs(adj, i, -1, vis)) {
                    return true;
                }
            }
        }

        return false;
    }
};


/*
Example Input:

V = 4

edges = {
    {0,1},
    {1,2},
    {2,3},
    {3,0}
}

Graph:

0 ----- 1
|       |
|       |
3 ----- 2


Example Output:

true

Explanation:
Cycle exists:
0 -> 1 -> 2 -> 3 -> 0
*/