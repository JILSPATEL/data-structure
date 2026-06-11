/**
 * Problem: Find Eventual Safe States
 * 
 * Description:
 * Return all nodes that are eventually safe in a directed graph.
 * A node is safe if every possible path starting from it
 * leads to a terminal node (node with no outgoing edges).
 *
 * Example 1:
 * Input: graph = [[1,2],[2,3],[5],[0],[5],[]]
 * Output: [2,4,5,6]
 * Explanation: Nodes 2,4,5,6 are safe states
 *
 * Example 2:
 * Input: graph = [[1,2],[2,3],[5],[0],[5],[]]
 * Output: [4,5,6]
 * Explanation: Nodes 4,5,6 eventually lead to terminal states
 *
 * Example 3:
 * Input: graph = [[1],[2],[3],[0]]
 * Output: []
 * Explanation: All nodes are in a cycle
 *
 * Approaches:
 * 1. DFS + Cycle Detection
 *    - Use recursion with visited/pathVisited arrays.
 *    - Nodes involved in cycles are unsafe.
 *    - Time: O(V + E)
 *
 * 2. BFS (Kahn's Algorithm on Reversed Graph) [Used]
 *    - Reverse all graph edges.
 *    - Store outdegree of original graph.
 *    - Start from terminal nodes (outdegree = 0).
 *    - Reduce outdegree of connected nodes in reversed graph.
 *    - Nodes reaching outdegree = 0 become safe.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();

        vector<vector<int>> revGraph(n);
        vector<int> outDeg(n, 0);

        // Build reverse graph and calculate outdegree
        for (int i = 0; i < n; i++) {
            outDeg[i] = graph[i].size();

            for (auto &v : graph[i]) {
                revGraph[v].push_back(i);
            }
        }

        queue<int> q;

        // Push terminal nodes
        for (int i = 0; i < n; i++) {
            if (outDeg[i] == 0) {
                q.push(i);
            }
        }

        vector<int> ans;

        // Kahn's Algorithm
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            ans.push_back(node);

            for (auto &neb : revGraph[node]) {
                outDeg[neb]--;

                if (outDeg[neb] == 0) {
                    q.push(neb);
                }
            }
        }

        sort(ans.begin(), ans.end());

        return ans;
    }
};
/**
 * Problem: Find Eventual Safe States
 * 
 * Description:
 * Return all nodes that are eventually safe in a directed graph.
 * A node is safe if every path starting from it eventually
 * reaches a terminal node.
 *
 * Approaches:
 * 1. DFS + Cycle Detection [Used]
 *    - Use visited and pathVisited arrays.
 *    - If a node is revisited in the current DFS path,
 *      a cycle exists.
 *    - Nodes involved in or reaching a cycle are unsafe.
 *
 * 2. BFS (Kahn's Algorithm on Reversed Graph)
 *    - Reverse graph and process nodes with outdegree = 0.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */

class Solution {
public:
    bool dfs(int node,
             vector<vector<int>>& graph,
             vector<int>& vis,
             vector<int>& pathVis,
             vector<int>& safe) {

        vis[node] = 1;
        pathVis[node] = 1;

        for (auto &neb : graph[node]) {

            // Unvisited node
            if (!vis[neb]) {
                if (dfs(neb, graph, vis, pathVis, safe)) {
                    return true;
                }
            }

            // Back edge -> cycle found
            else if (pathVis[neb]) {
                return true;
            }
        }

        // No cycle from this node
        pathVis[node] = 0;
        safe[node] = 1;

        return false;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();

        vector<int> vis(n, 0);
        vector<int> pathVis(n, 0);
        vector<int> safe(n, 0);

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, graph, vis, pathVis, safe);
            }
        }

        vector<int> ans;

        for (int i = 0; i < n; i++) {
            if (safe[i]) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};