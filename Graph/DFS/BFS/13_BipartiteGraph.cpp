/**
 * Problem: Is Graph Bipartite?
 *
 * A graph is bipartite if:
 * We can divide nodes into 2 sets such that
 * no two adjacent nodes belong to the same set.
 *
 * ---------------------------------------------------
 * BFS Approach:
 * ---------------------------------------------------
 * 1. Use a color array.
 *
 *      -1 -> Uncolored
 *       0 -> First color
 *       1 -> Second color
 *
 * 2. Start BFS from every unvisited node.
 *
 * 3. Color adjacent nodes with opposite color.
 *
 * 4. If two adjacent nodes have same color,
 *    graph is not bipartite.
 *
 * Example 1:
 * Input: graph = [[1,3],[0,2],[1,3],[0,2]]
 * Output: true
 * Explanation: Partition: {0,2}, {1,3}
 *
 * Example 2:
 * Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
 * Output: false
 * Explanation: No valid 2-coloring possible
 *
 * Example 3:
 * Input: graph = [[],[1],[0,3],[2]]
 * Output: true
 * Explanation: Partition: {0,3}, {1,2}
 *
 * ---------------------------------------------------
 * Time Complexity:
 * O(V + E)
 *
 * Space Complexity:
 * O(V)
 */

class Solution {
public:

    bool isBipartite(vector<vector<int>>& graph) {

        // Total number of nodes
        int n = graph.size();

        /**
         * Color array
         * -1 means unvisited/uncolored
         */
        vector<int> color(n, -1);

        // BFS queue
        queue<int> q;

        /**
         * Graph may be disconnected
         * so traverse every component
         */
        for (int i = 0; i < n; i++) {

            // If node is unvisited
            if (color[i] == -1) {

                // Assign first color
                color[i] = 0;

                // Push into queue
                q.push(i);

                // Standard BFS
                while (!q.empty()) {

                    // Get current node
                    int node = q.front();
                    q.pop();

                    // Traverse all neighbors
                    for (auto &neb : graph[node]) {

                        /**
                         * If neighbor is uncolored
                         * assign opposite color
                         */
                        if (color[neb] == -1) {

                            color[neb] = 1 - color[node];

                            q.push(neb);
                        }

                        /**
                         * If adjacent nodes
                         * have same color
                         */
                        else if (color[neb] == color[node]) {

                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }
};



//DFS Approach:

/**
 * Problem: Is Graph Bipartite?
 *
 * A graph is bipartite if:
 * We can divide all nodes into 2 groups such that
 * no adjacent nodes belong to the same group.
 *
 * ---------------------------------------------------
 * DFS Approach:
 * ---------------------------------------------------
 * 1. Use coloring technique.
 *
 *      -1 -> Not colored
 *       0 -> First color
 *       1 -> Second color
 *
 * 2. Start DFS from every unvisited node.
 *
 * 3. Assign alternate colors to adjacent nodes.
 *
 * 4. If two adjacent nodes get same color,
 *    graph is not bipartite.
 *
 * ---------------------------------------------------
 * Time Complexity:
 * O(V + E)
 *
 * Space Complexity:
 * O(V)
 * (including recursion stack)
 */

class Solution {
public:

    /**
     * DFS Traversal
     *
     * node  -> Current node
     * col   -> Current color
     */
    bool dfs(int node,
             int col,
             vector<vector<int>>& graph,
             vector<int>& color) {

        // Assign color
        color[node] = col;

        // Traverse neighbors
        for (auto &neb : graph[node]) {

            /**
             * If neighbor is uncolored
             */
            if (color[neb] == -1) {

                // Assign opposite color
                if (!dfs(neb,
                         1 - col,
                         graph,
                         color)) {

                    return false;
                }
            }

            /**
             * If adjacent nodes
             * have same color
             */
            else if (color[neb] == color[node]) {

                return false;
            }
        }

        return true;
    }

    bool isBipartite(vector<vector<int>>& graph) {

        // Total nodes
        int n = graph.size();

        /**
         * Initially all nodes are uncolored
         */
        vector<int> color(n, -1);

        /**
         * Graph can be disconnected
         */
        for (int i = 0; i < n; i++) {

            // If node is unvisited
            if (color[i] == -1) {

                // Start DFS with color 0
                if (!dfs(i,
                         0,
                         graph,
                         color)) {

                    return false;
                }
            }
        }

        return true;
    }
};